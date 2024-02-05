cmake_minimum_required(VERSION 3.30)
project(Sudoku-Solver CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/binaries)

set(BUILD_SHARED_LIBS OFF)

add_subdirectory(libraries/SFML)

add_executable(${PROJECT_NAME} ./sources/main.cpp)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
