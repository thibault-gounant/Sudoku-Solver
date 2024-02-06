#include "core.h"
#include "utils.h"

Sudoku::Sudoku() {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLUMNS; col++) {
            grid[index(row, col)].set();
            rows_remaining[row]++;
            cols_remaining[col]++;
            boxes_remaining[box(row, col)]++;
        }
    }
}

std::bitset<VALUES> Sudoku::values(int row, int col) {
    return grid[index(row, col)] & ~rows[row] & ~cols[col] & ~boxes[box(row, col)];
}

int Sudoku::get(int row, int col) {
    std::bitset<VALUES> bits = grid[index(row, col)];
    return bits.count() == 1 ? find_first(bits) : 0;
}

void Sudoku::set(int row, int col, int val) {
    if (val > 0 && val <= VALUES) {
        grid[index(row, col)].reset();
        grid[index(row, col)].set(val - 1);
        rows[row].set(val - 1);
        cols[col].set(val - 1);
        boxes[box(row, col)].set(val - 1);
        rows_remaining[row]--;
        cols_remaining[col]--;
        boxes_remaining[box(row, col)]--;
    }
}

void Sudoku::add(int row, int col, int val) {
    if (val > 0 && val <= VALUES) {
        store(row, col);
        grid[index(row, col)].set(val - 1);
        rows[row].set(val - 1);
        cols[col].set(val - 1);
        boxes[box(row, col)].set(val - 1);
    }
}

void Sudoku::remove(int row, int col, int val) {
    if (val > 0 && val <= VALUES) {
        store(row, col);
        grid[index(row, col)].reset(val - 1);
        rows[row].reset(val - 1);
        cols[col].reset(val - 1);
        boxes[box(row, col)].reset(val - 1);
    }
}

void Sudoku::store(int row, int col) {
    State state;
    state.row = row;
    state.col = col;
    state.values = grid[index(row, col)];
    state.row_values = rows[row];
    state.col_values = cols[col];
    state.box_values = boxes[box(row, col)];
    state.row_values_remaining = rows_remaining[row];
    state.col_values_remaining = cols_remaining[col];
    state.box_values_remaining = boxes_remaining[box(row, col)];
    states.push_back(state);
}

void Sudoku::restore() {
    if (!states.empty()) {
        State state = states.back();
        grid[index(state.row, state.col)] = state.values;
        rows[state.row] = state.row_values;
        cols[state.col] = state.col_values;
        boxes[box(state.row, state.col)] = state.box_values;
        rows_remaining[state.row] = state.row_values_remaining;
        cols_remaining[state.col] = state.col_values_remaining;
        boxes_remaining[box(state.row, state.col)] = state.box_values_remaining;
        states.pop_back();
    }
}
