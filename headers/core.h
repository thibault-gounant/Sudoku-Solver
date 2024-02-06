#ifndef CORE_H
#define CORE_H

#define ROWS 9
#define COLUMNS 9
#define BOXES 9
#define VALUES 9

#include <array>
#include <bitset>

class Sudoku {
private:
    std::array<int, ROWS * COLUMNS> matrix = {};
    std::array<std::bitset<VALUES>, ROWS> rows;
    std::array<std::bitset<VALUES>, COLUMNS> cols;
    std::array<std::bitset<VALUES>, BOXES> boxes;

    static int index(const int row, const int col) {
        return row * COLUMNS + col;
    }

    static int box(const int row, const int col) {
        return (row / 3) * COLUMNS / 3 + (col / 3);
    }

public:
    Sudoku(const std::array<int, ROWS * COLUMNS>& init);
    ~Sudoku() = default; // no dynamic allocation

    int get(const int row, const int col);
    void set(const int row, const int col, const int val);
    void clear(const int row, const int col);

    std::bitset<VALUES> possibilities(const int row, const int col);
};

#endif
