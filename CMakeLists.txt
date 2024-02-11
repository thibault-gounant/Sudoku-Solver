cmake_minimum_required(VERSION 3.30)
project(Sudoku-Solver CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/binaries)
set(CMAKE_CXX_FLAGS "-O2")

set(BUILD_SHARED_LIBS OFF)

include_directories(${PROJECT_SOURCE_DIR}/headers)

add_subdirectory(libraries/SFML)

aux_source_directory(./sources/core CORE)
aux_source_directory(./sources/utils UTILS)

add_executable(${PROJECT_NAME} ./sources/main.cpp ${CORE} ${UTILS})
add_executable(${PROJECT_NAME}_tests ./tests/test.cpp ${CORE} ${UTILS})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
target_link_libraries(${PROJECT_NAME}_tests sfml-graphics sfml-window sfml-system)

enable_testing()
add_test(NAME norvig_hardest_1_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/inputs/1 ${PROJECT_SOURCE_DIR}/tests/solutions/1)
add_test(NAME norvig_hardest_2_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/inputs/2 ${PROJECT_SOURCE_DIR}/tests/solutions/2)
add_test(NAME norvig_hardest_3_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/inputs/3 ${PROJECT_SOURCE_DIR}/tests/solutions/3)
add_test(NAME norvig_hardest_4_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/inputs/4 ${PROJECT_SOURCE_DIR}/tests/solutions/4)
add_test(NAME norvig_hardest_5_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/inputs/5 ${PROJECT_SOURCE_DIR}/tests/solutions/5)
add_test(NAME norvig_hardest_6_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/inputs/6 ${PROJECT_SOURCE_DIR}/tests/solutions/6)
add_test(NAME norvig_hardest_7_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/inputs/7 ${PROJECT_SOURCE_DIR}/tests/solutions/7)
add_test(NAME norvig_hardest_8_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/inputs/8 ${PROJECT_SOURCE_DIR}/tests/solutions/8)
add_test(NAME norvig_hardest_9_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/inputs/9 ${PROJECT_SOURCE_DIR}/tests/solutions/9)
add_test(NAME norvig_hardest_10_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/inputs/10 ${PROJECT_SOURCE_DIR}/tests/solutions/10)
add_test(NAME norvig_hardest_11_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/inputs/11 ${PROJECT_SOURCE_DIR}/tests/solutions/11)
