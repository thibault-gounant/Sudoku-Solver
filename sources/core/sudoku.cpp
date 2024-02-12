#include "core.h"
#include "utils.h"

#include <algorithm>
#include <set>

Sudoku::Sudoku() {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLUMNS; ++col) {

            grid[index(row, col)].set();

            neighbors[index(row,col)].reserve((ROWS - 1) + (COLUMNS - 1) + (BOXES - 1) - (ROWS_BOXES - 1) - (COLUMNS_BOXES - 1));

            std::set<Cell> set;

            for (const auto& cell : row_cells(row)){
                set.insert(cell);
            }

            for (const auto& cell : col_cells(col)){
                set.insert(cell);
            }

            for (const auto& cell : box_cells(row, col)){
                set.insert(cell);
            }

            set.erase(Cell(row, col));

            neighbors[index(row, col)].assign(set.begin(), set.end());
        }
    }
}

int Sudoku::get(const int row, const int col) {
    return find_first(grid[index(row, col)]);
}

void Sudoku::set(const int row, const int col, const int value) {
    if (value > 0 && value <= VALUES) {
        grid[index(row, col)].reset();
        grid[index(row, col)].set(value - 1);
        rows[row].set(value - 1);
        cols[col].set(value - 1);
        boxes[box(row, col)].set(value - 1);
    }
}

void Sudoku::add(const int row, const int col, const int value) {
    if (value > 0 && value <= VALUES) {
        grid[index(row, col)].set(value - 1);
    }
}

void Sudoku::remove(const int row, const int col, const int value) {
    if (value > 0 && value <= VALUES) {
        grid[index(row, col)].reset(value - 1);
    }
}

void Sudoku::store() {
    State state;
    state.grid = grid;
    state.rows = rows;
    state.cols = cols;
    state.boxes = boxes;
    states.push_back(state);
}

void Sudoku::restore() {
    if (!states.empty()) {
        State state = states.back();
        grid = state.grid;
        rows = state.rows;
        cols = state.cols;
        boxes = state.boxes;
        states.pop_back();
    }
}

const std::bitset<VALUES> Sudoku::get_values(const int row, const int col) {
    return grid[index(row, col)] & ~rows[row] & ~cols[col] & ~boxes[box(row, col)];
}

const std::vector<Cell> Sudoku::get_neighbors(const int row, const int col) {
    return neighbors[index(row, col)];
}
