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

using Cell = std::pair<int, int>;

struct State {
    std::array<std::bitset<VALUES>, ROWS * COLUMNS> grid = {};
    std::array<std::bitset<VALUES>, ROWS> rows = {};
    std::array<std::bitset<VALUES>, COLUMNS> cols = {};
    std::array<std::bitset<VALUES>, BOXES> boxes = {};
};

class Sudoku {
private:
    std::array<std::bitset<VALUES>, ROWS * COLUMNS> grid = {};

    std::array<std::bitset<VALUES>, ROWS> rows = {};
    std::array<std::bitset<VALUES>, COLUMNS> cols = {};
    std::array<std::bitset<VALUES>, BOXES> boxes = {};

    std::array<std::vector<Cell>, ROWS * COLUMNS> neighbors = {};

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

    void store();
    void restore();

    std::bitset<VALUES> get_values(int row, int col);
    std::vector<Cell> get_neighbors(int row, int col);
};

void solve(Sudoku &sudoku);

#endif
