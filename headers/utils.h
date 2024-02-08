#ifndef UTILS_H
#define UTILS_H

#define WIDTH 800
#define HEIGHT 600

#include <iostream>
#include <array>
#include <bitset>
#include <vector>

constexpr int VALUES = 9;

constexpr int ROWS = 9;
constexpr int COLUMNS = 9;
constexpr int ROWS_BOXES = 3;
constexpr int COLUMNS_BOXES = 3;

class Sudoku;

struct State;

using Cell = std::pair<int, int>;

template <typename T>
struct Optional {
    T value;
    bool has_value;
    Optional() : value(), has_value(false)  {}
    Optional(const T& val) : value(val), has_value(true) {}
};

void print_usage(char *argv[]);
void print_test_result(const bool result, const char message[]);

int row(int index);
int col(int index);
int index(int row, int col);
int box(int row, int col);

int find_first(std::bitset<VALUES> values);

void read(Sudoku& sudoku, char* filename);
void write(Sudoku& sudoku, char* filename);

bool is_valid(Sudoku& sudoku);
bool is_solved(Sudoku& sudoku);
bool is_equal(Sudoku& a, Sudoku& b);

#endif
