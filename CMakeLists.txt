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
add_test(NAME empty_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/1/input ${PROJECT_SOURCE_DIR}/tests/1/output)
add_test(NAME full_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/2/input ${PROJECT_SOURCE_DIR}/tests/2/output)
add_test(NAME ordinary_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/3/input ${PROJECT_SOURCE_DIR}/tests/3/output)
add_test(NAME symmetrical_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/4/input ${PROJECT_SOURCE_DIR}/tests/4/output)
add_test(NAME ai_escargot_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/5/input ${PROJECT_SOURCE_DIR}/tests/5/output)
add_test(NAME platinum_blonde_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/6/input ${PROJECT_SOURCE_DIR}/tests/6/output)
add_test(NAME golden_nugget_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/7/input ${PROJECT_SOURCE_DIR}/tests/7/output)
add_test(NAME easter_monster_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/8/input ${PROJECT_SOURCE_DIR}/tests/8/output)
add_test(NAME norvig_impossible_sudoku_tests COMMAND ${PROJECT_NAME}_tests ${PROJECT_SOURCE_DIR}/tests/9/input ${PROJECT_SOURCE_DIR}/tests/9/output)
