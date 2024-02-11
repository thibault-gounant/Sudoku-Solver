#include "core.h"
#include "utils.h"

#include <cassert>

static void test_runner(char* input, char* solution) {

    Sudoku actual;
    read(actual, input);

    bool valid = is_valid(actual);

    solve(actual);

    bool solved = is_solved(actual);

    Sudoku expected;
    read(expected, solution);

    bool equal = is_equal(expected, actual);

    print_test_result(valid && solved && equal, "Sudoku solved\n");
    assert(valid && solved && equal);
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        print_usage(argv);
        return EXIT_FAILURE;
    }

    test_runner(argv[1], argv[2]);

    return EXIT_SUCCESS;
}
