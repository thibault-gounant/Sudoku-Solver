#ifndef CORE_H
#define CORE_H

#include "utils.h"

struct State {
    int row;
    int col;

    std::bitset<VALUES> values;
    std::bitset<VALUES> row_values;
    std::bitset<VALUES> col_values;
    std::bitset<VALUES> box_values;

    int row_values_remaining;
    int col_values_remaining;
    int box_values_remaining;
};

class Sudoku {
private:
    std::array<std::bitset<VALUES>, ROWS * COLUMNS> grid;
    std::array<std::bitset<VALUES>, ROWS> rows;
    std::array<std::bitset<VALUES>, COLUMNS> cols;
    std::array<std::bitset<VALUES>, ROWS_BOXES * COLUMNS_BOXES> boxes;

    std::array<int, ROWS> rows_remaining;
    std::array<int, COLUMNS> cols_remaining;
    std::array<int, ROWS_BOXES * COLUMNS_BOXES> boxes_remaining;

    std::vector<State> states;

public:
    Sudoku();
    ~Sudoku() = default; // no dynamic memory allocation

    std::bitset<VALUES> values(int row, int col);

    // Used for defined values
    int get(int row, int col);
    void set(int row, int col, int val);

    // Used for possible values
    void add(int row, int col, int val);
    void remove(int row, int col, int val);

    void store(int row, int col);
    void restore();
};

#endif
