#include "core.h"

static std::vector<Cell> remaining_cells(Sudoku &sudoku) {

    std::vector<Cell> cells;

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLUMNS; ++col) {
            if (sudoku.get(row, col) == 0) {
                cells.emplace_back(row, col);
            }
        }
    }

    return cells;
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

    bool solved = cache.empty();

    if (!solved) {

        Cell current = cache.back();
        cache.pop_back();

        const int row = current.first;
        const int col = current.second;

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
    backtracking(sudoku, remaining_cells(sudoku));
}
