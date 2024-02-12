#include "core.h"

#include <fstream>

void print_usage(char *argv[]) {
    fprintf(stderr, "Usage: %s <input filename> <output filename>\n", argv[0]);
}

void print_test_result(const bool result, const char* message) {
    result ?
    fprintf(stdout, "\033[0;32m✅ PASS\033[0m\t%s", message) :
    fprintf(stderr, "\033[1;31m❌ FAIL\033[0m\t%s", message);
}

int row(const int index) {
    return index / COLUMNS;
}

int col(const int index) {
    return index % COLUMNS;
}

int index(const int row, const int col) {
    return row * COLUMNS + col;
}

int box(const int row, const int col) {
    return (row / ROWS_BOXES) * COLUMNS / COLUMNS_BOXES + (col / COLUMNS_BOXES);
}

std::vector<Cell> row_cells(const int row) {

    std::vector<Cell> cells;
    cells.reserve(COLUMNS);

    for (int col = 0; col < COLUMNS; ++col) {
        cells.emplace_back(row, col);
    }

    return cells;
}

std::vector<Cell> col_cells(const int col) {

    std::vector<Cell> cells;
    cells.reserve(ROWS);

    for (int row = 0; row < ROWS; ++row) {
        cells.emplace_back(row, col);
    }

    return cells;
}

std::vector<Cell> box_cells(const int row, const int col) {

    std::vector<Cell> cells;
    cells.reserve(ROWS_BOXES * COLUMNS_BOXES);

    const int br = (row / ROWS_BOXES) * ROWS_BOXES;
    const int bc = (col / COLUMNS_BOXES) * COLUMNS_BOXES;

    for (int r = 0; r < ROWS_BOXES; ++r) {
        for (int c = 0; c < COLUMNS_BOXES; ++c) {
            cells.emplace_back(br + r, bc + c);
        }
    }

    return cells;
}

int find_first(const std::bitset<VALUES> values) {

    int first_value = 0;

    if (values.count() == 1) {
        for (int value = 1; value <= VALUES && first_value == 0; ++value) {
            if (values.test(value - 1)) {
                first_value = value;
            }
        }
    }

    return first_value;
}

void read(Sudoku& sudoku, const std::string filename) {

    std::ifstream file(filename);
    if (file.fail()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    char c;
    int index = 0;

    while (file >> c && index < ROWS * COLUMNS) {
        if (c >= '1' && c <= '9') {
            sudoku.set(row(index), col(index), c - '0');
            index++;
        }
        if (c == '0' || c == '.') {
            sudoku.set(row(index), col(index), 0);
            index++;
        }
    }

    file.close();
}

void write(Sudoku& sudoku, const std::string filename) {

    std::ofstream file(filename);
    if (file.fail()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    for (int row = 0; row < ROWS; ++row) {
        if (row % 3 == 0 && row != 0) {
            file << "------+-------+------\n";
        }
        for (int col = 0; col < COLUMNS; ++col) {
            if (col % 3 == 0 && col != 0) {
                file << "| ";
            }
            file << sudoku.get(row, col) << ' ';
        }
        file << '\n';
    }

    file.close();
}

bool is_valid(Sudoku& sudoku) {

    std::array<std::bitset<VALUES>, ROWS> rows = {};
    std::array<std::bitset<VALUES>, COLUMNS> cols = {};
    std::array<std::bitset<VALUES>, BOXES> boxes = {};

    bool valid = true;

    for (int row = 0; row < ROWS && valid; ++row) {
        for (int col = 0; col < COLUMNS && valid; ++col) {

            const int value = sudoku.get(row, col);

            if (value > 0) {
                valid = !rows[row].test(value - 1) &&
                        !cols[col].test(value - 1) &&
                        !boxes[box(row, col)].test(value - 1);

                rows[row].set(value - 1);
                cols[col].set(value - 1);
                boxes[box(row, col)].set(value - 1);
            }
        }
    }

    return valid;
}

bool is_solved(Sudoku& sudoku) {

    std::array<std::bitset<VALUES>, ROWS> rows = {};
    std::array<std::bitset<VALUES>, COLUMNS> cols = {};
    std::array<std::bitset<VALUES>, BOXES> boxes = {};

    bool solved = true;

    for (int row = 0; row < ROWS && solved; ++row) {
        for (int col = 0; col < COLUMNS && solved; ++col) {

            const int value = sudoku.get(row, col);

            solved = value > 0 &&
                     !rows[row].test(value - 1) &&
                     !cols[col].test(value - 1) &&
                     !boxes[box(row, col)].test(value - 1);

            if (solved) {
                rows[row].set(value - 1);
                cols[col].set(value - 1);
                boxes[box(row, col)].set(value - 1);
            }
        }
    }

    return solved;
}

bool is_equal(Sudoku& a, Sudoku& b) {

    bool equal = true;

    for (int row = 0; row < ROWS && equal; ++row) {
        for (int col = 0; col < COLUMNS && equal; ++col) {
            equal = a.get(row, col) == b.get(row, col);
        }
    }

    return equal;
}
