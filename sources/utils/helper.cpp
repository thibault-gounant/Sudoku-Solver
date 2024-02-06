#include <fstream>

#include "core.h"

void print_usage(char *argv[]) {
    fprintf(stderr, "Usage: %s <input filename> <output filename>\n", argv[0]);
}

void print_test_result(const bool result, const char message[]) {
    result ?
    fprintf(stdout, "\033[0;32m✅ PASS\033[0m\t%s", message) :
    fprintf(stderr, "\033[1;31m❌ FAIL\033[0m\t%s", message);
}

int row(int index) {
    return index / COLUMNS;
}

int col(int index) {
    return index % COLUMNS;
}

int index(int row, int col) {
    return row * COLUMNS + col;
}

int box(int row, int col) {
    return (row / ROWS_BOXES) * COLUMNS / COLUMNS_BOXES + (col / COLUMNS_BOXES);
}

void read(Sudoku& sudoku, char* filename) {

    std::ifstream file(filename);
    if (file.fail()) {
        throw std::runtime_error("Failed to open file: " + std::string(filename));
    }

    char c;
    int index = 0;

    while (file >> c && index < ROWS * COLUMNS) {
        if (c >= '0' && c <= '9') {
            sudoku.set(row(index), col(index), c - '0');
            index++;
        }
    }

    file.close();
}

void write(Sudoku& sudoku, char* filename) {

    std::ofstream file(filename);
    if (file.fail()) {
        throw std::runtime_error("Failed to open file: " + std::string(filename));
    }

    for (int row = 0; row < ROWS; row++) {
        if (row % 3 == 0 && row != 0) {
            file << "------+-------+------\n";
        }
        for (int col = 0; col < COLUMNS; col++) {
            if (col % 3 == 0 && col != 0) {
                file << "| ";
            }
            file << sudoku.get(row, col) << ' ';
        }
        file << '\n';
    }

    file.close();
}

int find_first(std::bitset<VALUES> values) {

    int value = 0;

    if (values.count() == 1) {
        for (int i = 0; i < VALUES; ++i) {
            if (values.test(i)) {
                return i + 1;
            }
        }
    }

    return value;
}

bool is_valid(Sudoku& sudoku) {

    std::array<std::bitset<VALUES>, ROWS> rows{};
    std::array<std::bitset<VALUES>, COLUMNS> cols{};
    std::array<std::bitset<VALUES>, ROWS_BOXES * COLUMNS_BOXES> boxes{};

    bool valid = true;

    for (int row = 0; row < ROWS && valid; row++) {
        for (int col = 0; col < COLUMNS && valid; col++) {
            int val = sudoku.get(row, col);
            if (val > 0) {
                valid = !rows[row].test(val - 1) &&
                        !cols[col].test(val - 1) &&
                        !boxes[box(row, col)].test(val - 1);

                rows[row].set(val - 1);
                cols[col].set(val - 1);
                boxes[box(row, col)].set(val - 1);
            }
        }
    }

    return valid;
}

bool is_equal(Sudoku& a, Sudoku& b) {

    bool equal = true;

    for (int row = 0; row < ROWS && equal; row++) {
        for (int col = 0; col < COLUMNS && equal; col++) {
            equal = a.get(row, col) == b.get(row, col);
        }
    }

    return equal;
}
