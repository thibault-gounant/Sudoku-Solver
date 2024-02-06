#include "core.h"
#include "utils.h"

#include <cassert>

static void test_runner(char* input, char* output) {

    Sudoku sudoku;
    read(sudoku, input);

    bool valid = is_valid(sudoku);
    print_test_result(valid, "Read input\n");

    write(sudoku, output);

    Sudoku result;
    read(result, output);

    bool equal = is_equal(sudoku, result);
    print_test_result(equal, "Write output\n");

    assert(valid && equal);
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        print_usage(argv);
        return EXIT_FAILURE;
    }

    test_runner(argv[1], argv[2]);

    return EXIT_SUCCESS;
}
