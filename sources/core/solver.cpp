#include "core.h"
#include "utils.h"

#include <algorithm>

static Optional<Cell> next_cell(Sudoku& sudoku, std::vector<Cell>& cache) {

    int minimum_remaining_values = VALUES + 1;
    int highest_degree = -1;
    int best_index = -1;

    for (int index = 0; index < cache.size(); ++index) {

        auto [row, col] = cache[index];

        const int remaining_values = sudoku.values(row, col).count();
        const int degree = sudoku.remaining_values(row, col);

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

static std::vector<int> available_values(Sudoku &sudoku, const int row, const int col) {

    const std::bitset<VALUES> possibilities = sudoku.values(row, col);

    std::vector<int> least_constraining_values;
    least_constraining_values.reserve(possibilities.count());

    for (int value = 1; value <= VALUES; ++value) {
        if (possibilities.test(value - 1)) {
            least_constraining_values.emplace_back(value);
        }
    }

    auto constraints = [&](const int value) {
        sudoku.store(row, col);
        sudoku.set(row, col, value);
        const int score = sudoku.constraining_values(row, col);
        sudoku.restore();
        return score;
    };

    std::sort(least_constraining_values.begin(), least_constraining_values.end(), [&](const int a, const int b) {
        return constraints(a) < constraints(b);
    });

    return least_constraining_values;
}

static bool backtracking(Sudoku &sudoku, std::vector<Cell> cache) {

    Optional<Cell> cell = next_cell(sudoku, cache);

    bool solved = cache.empty() && !cell.has_value;

    if (!solved) {

        auto [row, col] = cell.value;

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
