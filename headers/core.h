#ifndef CORE_H
#define CORE_H

#include <array>
#include <bitset>
#include <vector>

constexpr int VALUES = 9;
constexpr int ROWS = 9;
constexpr int COLUMNS = 9;
constexpr int BOXES = 9;
constexpr int ROWS_BOXES = 3;
constexpr int COLUMNS_BOXES = 3;

struct State {

    int row;
    int col;

    std::bitset<VALUES> values;
    std::bitset<VALUES> row_values;
    std::bitset<VALUES> col_values;
    std::bitset<VALUES> box_values;

    int row_remaining_values;
    int col_remaining_values;
    int box_remaining_values;

    int row_constraining_values;
    int col_constraining_values;
    int box_constraining_values;
};

class Sudoku {

private:

    std::array<std::bitset<VALUES>, ROWS * COLUMNS> grid = {};
    std::array<std::bitset<VALUES>, ROWS> rows = {};
    std::array<std::bitset<VALUES>, COLUMNS> cols = {};
    std::array<std::bitset<VALUES>, BOXES> boxes = {};

    std::array<int, ROWS> rows_remaining = {};
    std::array<int, COLUMNS> cols_remaining = {};
    std::array<int, BOXES> boxes_remaining = {};

    std::array<int, ROWS> rows_constraining = {};
    std::array<int, COLUMNS> cols_constraining = {};
    std::array<int, BOXES> boxes_constraining = {};

    std::vector<State> states;

public:

    Sudoku();
    ~Sudoku() = default; // no dynamic memory allocation

    // Used for defined values
    int get(int row, int col);
    void set(int row, int col, int value);

    // Used for possible values
    void add(int row, int col, int value);
    void remove(int row, int col, int value);

    void store(int row, int col);
    void restore();

    std::bitset<VALUES> values(int row, int col);

    int remaining_values(int row, int col);
    int constraining_values(int row, int col);
};

void solve(Sudoku &sudoku);

#endif
