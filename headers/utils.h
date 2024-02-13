#ifndef UTILS_H
#define UTILS_H

#define WIDTH 800
#define HEIGHT 600

template <typename T>
struct Optional {
    T value;
    bool has_value;
    Optional() : value(), has_value(false)  {}
    Optional(const T &val) : value(val), has_value(true) {}
};

void print_usage(char *argv[]);

int row(int index);
int col(int index);

int index(int row, int col);
int box(int row, int col);

std::vector<Cell> row_cells(int row);
std::vector<Cell> col_cells(int col);
std::vector<Cell> box_cells(int row, int col);

int find_first(std::bitset<VALUES> values);

void read(Sudoku &sudoku, std::string filename);
void write(Sudoku &sudoku, std::string filename);

bool is_valid(Sudoku &sudoku);
bool is_solved(Sudoku &sudoku);
bool is_equal(Sudoku &a, Sudoku &b);

#endif
