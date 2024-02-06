#include "core.h"

Sudoku::Sudoku(const std::array<int, ROWS * COLUMNS>& init) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            this->set(row, col, init[index(row, col)]);
        }
    }
}

int Sudoku::get(const int row, const int col) {
    return matrix[index(row, col)];
}

void Sudoku::set(const int row, const int col, const int val) {
    if (val > 0 && val <= VALUES) {
        matrix[index(row, col)] = val;
        rows[row].set(val - 1);
        cols[col].set(val - 1);
        boxes[box(row, col)].set(val - 1);
    }
}

void Sudoku::clear(const int row, const int col) {
    const int val = matrix[index(row, col)];
    matrix[index(row, col)] = 0;
    rows[row].reset(val - 1);
    cols[col].reset(val - 1);
    boxes[box(row, col)].reset(val - 1);
}

std::bitset<VALUES> Sudoku::possibilities(const int row, const int col) {
    std::bitset<VALUES> result;
    result.set();
    result &= ~rows[row];
    result &= ~cols[col];
    result &= ~boxes[box(row, col)];
    return result;
}
