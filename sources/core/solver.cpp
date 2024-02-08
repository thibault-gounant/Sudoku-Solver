#include "core.h"

static Optional<Cell> minimum_remaining_value(Sudoku& sudoku, std::vector<Cell>& cache) {

    int minimum = VALUES + 1;
    int index = -1;

    for (int i = 0; i < cache.size(); ++i) {
        int count = sudoku.values(cache[i].first, cache[i].second).count();
        if (count > 0 && count < minimum) {
            minimum = count;
            index = i;
        }
    }

    Optional<Cell> result;
    if (index > -1) {
        result = Optional<Cell>(cache[index]);
        cache.erase(cache.begin() + index);
    }

    return result;
}

static std::vector<int> available_values(Sudoku &sudoku, int row, int col) {

    std::bitset<VALUES> possibilities = sudoku.values(row, col);

    std::vector<int> values;
    values.reserve(possibilities.count());

    for (int val = 1; val <= VALUES; ++val) {
        if (possibilities.test(val - 1)) {
            values.emplace_back(val);
        }
    }

    return values;
}

static bool backtracking(Sudoku &sudoku, std::vector<Cell> cache) {

    Optional<Cell> cell = minimum_remaining_value(sudoku, cache);
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
