#include "core.h"

static Optional<Cell> next_cell(Sudoku& sudoku, std::vector<Cell>& cache) {

    int minimum_remaining_values = VALUES + 1;
    int highest_degree = -1;
    int best_index = -1;

    for (int index = 0; index < cache.size(); ++index) {

        const int row = cache[index].first;
        const int col = cache[index].second;

        const int remaining_values = sudoku.values(row, col).count();
        const int degree = sudoku.get_row_remaining(row) + sudoku.get_col_remaining(col) + sudoku.get_box_remaining(box(row, col));

        if (remaining_values > 0 && (remaining_values < minimum_remaining_values || (remaining_values == minimum_remaining_values && degree > highest_degree))) {
            minimum_remaining_values = remaining_values;
            highest_degree = degree;
            best_index = index;
        }
    }

    Optional<Cell> cell;
    if (best_index > -1) {
        cell = Optional<Cell>(cache[best_index]);
        cache.erase(cache.begin() + best_index);
    }

    return cell;
}

static std::vector<int> available_values(Sudoku &sudoku, int row, int col) {

    std::bitset<VALUES> possibilities = sudoku.values(row, col);

    std::vector<int> values;
    values.reserve(possibilities.count());

    for (int value = 1; value <= VALUES; ++value) {
        if (possibilities.test(value - 1)) {
            values.emplace_back(value);
        }
    }

    return values;
}

static bool backtracking(Sudoku &sudoku, std::vector<Cell> cache) {

    Optional<Cell> cell = next_cell(sudoku, cache);
    bool solved = cache.empty() && !cell.has_value;

    if (!solved) {

        const int row = cell.value.first;
        const int col = cell.value.second;

        std::vector<int> values = available_values(sudoku, row, col);

        for (auto value = values.begin(); value != values.end() && !solved; ++value) {

            sudoku.store(row, col);
            sudoku.set(row, col, *value);

            solved = backtracking(sudoku, cache);

            if (!solved) {
                sudoku.restore();
            }
        }
    }

    return solved;
}

void solve(Sudoku &sudoku) {

    std::vector<Cell> remaining_cells;
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLUMNS; ++col) {
            if (sudoku.get(row, col) == 0) {
                remaining_cells.emplace_back(row, col);
            }
        }
    }

    backtracking(sudoku, remaining_cells);
}
