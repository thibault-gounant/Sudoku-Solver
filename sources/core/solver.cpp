#include "core.h"
#include "utils.h"

#include <algorithm>
#include <queue>

static Optional<Cell> next_cell(Sudoku& sudoku, std::vector<Cell>& cache) {

    int minimum_remaining_values = VALUES + 1;
    int highest_degree = -1;
    int best_index = -1;

    for (int index = 0; index < cache.size(); ++index) {

        const int row = cache[index].first;
        const int col = cache[index].second;

        const int remaining_values = sudoku.get_values(row, col).count();

        int degree = 0;
        std::vector<Cell> neighbors = sudoku.get_neighbors(row, col);
        for (const Cell neighbor : neighbors) {
            const int r = neighbor.first;
            const int c = neighbor.second;
            if (sudoku.get(r, c) == 0) {
                degree += 1;
            }
        }

        if (remaining_values > 0 && (remaining_values < minimum_remaining_values || (remaining_values == minimum_remaining_values && degree > highest_degree))) {
            minimum_remaining_values = remaining_values;
            highest_degree = degree;
            best_index = index;
        }
    }

    Optional<Cell> cell;
    if (best_index > -1) {
        cell = Optional<Cell>(cache[best_index]);
        cache.erase(cache.begin() + best_index);
    }

    return cell;
}

static std::vector<int> available_values(Sudoku &sudoku, const int row, const int col) {

    const std::bitset<VALUES> possibilities = sudoku.get_values(row, col);

    std::vector<int> least_constraining_values;
    least_constraining_values.reserve(possibilities.count());

    for (int value = 1; value <= VALUES; ++value) {
        if (possibilities.test(value - 1)) {
            least_constraining_values.emplace_back(value);
        }
    }

    auto constraints = [&](const int value) {
        sudoku.store();
        sudoku.set(row, col, value);
        int score = 0;
        const std::vector<Cell> neighbors = sudoku.get_neighbors(row, col);
        for (const Cell neighbor : neighbors) {
            const int r = neighbor.first;
            const int c = neighbor.second;
            if (sudoku.get(r, c) == 0) {
                score += sudoku.get_values(r, c).count();
            }
        }
        sudoku.restore();
        return score;
    };

    std::sort(least_constraining_values.begin(), least_constraining_values.end(), [&](const int a, const int b) {
        return constraints(a) > constraints(b);
    });

    return least_constraining_values;
}

static bool constraint_propagation(Sudoku& sudoku, const int row, const int col, int& nb) {

    bool consistent = true;

    std::queue<Cell> queue = {};
    queue.push(Cell{row, col});

    while (!queue.empty() && consistent) {

        const Cell current = queue.front();
        queue.pop();

        std::vector<Cell> neighbors = sudoku.get_neighbors(current.first, current.second);

        for (int i = 0; i < neighbors.size() && consistent; ++i) {

            const int r = neighbors[i].first;
            const int c = neighbors[i].second;

            if (sudoku.get(r, c) == 0) {

                std::bitset<VALUES> values = sudoku.get_values(r, c);

                if (values.none()) {
                    consistent = false;
                }

                if (values.count() == 1) {
                    sudoku.store();
                    ++nb;
                    sudoku.set(r, c, find_first(values));
                    queue.push(Cell{r, c});
                }
            }
        }
    }

    return consistent;
}

static bool backtracking(Sudoku &sudoku, std::vector<Cell> cache) {

    cache.erase(std::remove_if(cache.begin(), cache.end(),
                  [&](const Cell& c){ return sudoku.get(c.first, c.second) != 0; }),
                cache.end());

    const Optional<Cell> cell = next_cell(sudoku, cache);

    bool solved = cache.empty() && !cell.has_value;

    if (!solved) {

        const int row = cell.value.first;
        const int col = cell.value.second;

        std::vector<int> values = available_values(sudoku, row, col);

        for (auto value = values.begin(); value != values.end() && !solved; ++value) {

            sudoku.store();
            int nb = 1;
            sudoku.set(row, col, *value);

            if (constraint_propagation(sudoku, row, col, nb)) {
                solved = backtracking(sudoku, cache);
            }

            if (!solved) {
                while (nb > 0) {
                    sudoku.restore();
                    --nb;
                }
            }
        }
    }

    return solved;
}

void solve(Sudoku &sudoku) {

    std::vector<Cell> remaining_cells;
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLUMNS; ++col) {
            if (sudoku.get(row, col) == 0) {
                remaining_cells.emplace_back(row, col);
            }
        }
    }

    backtracking(sudoku, remaining_cells);
}
