#include "core.h"
#include "utils.h"

Sudoku::Sudoku() {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLUMNS; ++col) {
            grid[index(row, col)].set();
            rows_remaining[row]++;
            cols_remaining[col]++;
            boxes_remaining[box(row, col)]++;
        }
    }
}

int Sudoku::get(const int row, const int col) {

    const std::bitset<VALUES> values = grid[index(row, col)];

    int first_value = 0;
    if (values.count() == 1) {
        for (int value = 0; value < VALUES && first_value == 0; ++value) {
            if (values.test(value)) {
                first_value = value + 1;
            }
        }
    }
    return first_value;
}

void Sudoku::set(const int row, const int col, const int value) {
    if (value > 0 && value <= VALUES) {
        grid[index(row, col)].reset();
        grid[index(row, col)].set(value - 1);
        rows[row].set(value - 1);
        cols[col].set(value - 1);
        boxes[box(row, col)].set(value - 1);
        rows_remaining[row]--;
        cols_remaining[col]--;
        boxes_remaining[box(row, col)]--;
        rows_constraining[row]++;
        cols_constraining[col]++;
        boxes_constraining[box(row, col)]++;
    }
}

void Sudoku::add(const int row, const int col, const int value) {
    if (value > 0 && value <= VALUES) {
        store(row, col);
        grid[index(row, col)].set(value - 1);
        rows[row].set(value - 1);
        cols[col].set(value - 1);
        boxes[box(row, col)].set(value - 1);
        rows_constraining[row]++;
        cols_constraining[col]++;
        boxes_constraining[box(row, col)]++;
    }
}

void Sudoku::remove(const int row, const int col, const int value) {
    if (value > 0 && value <= VALUES) {
        store(row, col);
        grid[index(row, col)].reset(value - 1);
        rows[row].reset(value - 1);
        cols[col].reset(value - 1);
        boxes[box(row, col)].reset(value - 1);
        rows_constraining[row]--;
        cols_constraining[col]--;
        boxes_constraining[box(row, col)]--;
    }
}

void Sudoku::store(const int row, const int col) {
    State state;
    state.row = row;
    state.col = col;
    state.values = grid[index(row, col)];
    state.row_values = rows[row];
    state.col_values = cols[col];
    state.box_values = boxes[box(row, col)];
    state.row_remaining_values = rows_remaining[row];
    state.col_remaining_values = cols_remaining[col];
    state.box_remaining_values = boxes_remaining[box(row, col)];
    state.row_constraining_values = rows_constraining[row];
    state.col_constraining_values = cols_constraining[col];
    state.box_constraining_values = boxes_constraining[box(row, col)];
    states.push_back(state);
}

void Sudoku::restore() {
    if (!states.empty()) {
        State state = states.back();
        grid[index(state.row, state.col)] = state.values;
        rows[state.row] = state.row_values;
        cols[state.col] = state.col_values;
        boxes[box(state.row, state.col)] = state.box_values;
        rows_remaining[state.row] = state.row_remaining_values;
        cols_remaining[state.col] = state.col_remaining_values;
        boxes_remaining[box(state.row, state.col)] = state.box_remaining_values;
        rows_constraining[state.row] = state.row_constraining_values;
        cols_constraining[state.col] = state.col_constraining_values;
        boxes_constraining[box(state.row, state.col)] = state.box_constraining_values;
        states.pop_back();
    }
}

std::bitset<VALUES> Sudoku::values(const int row, const int col) {
    return grid[index(row, col)] & ~rows[row] & ~cols[col] & ~boxes[box(row, col)];
}

int Sudoku::remaining_values(const int row, const int col) {
    return rows_remaining[row] + cols_remaining[col] + boxes_remaining[box(row, col)];
}

int Sudoku::constraining_values(const int row, const int col) {
    return rows_constraining[row] + cols_constraining[col] + boxes_constraining[box(row, col)];
}
