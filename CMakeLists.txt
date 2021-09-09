cmake_minimum_required(VERSION 3.17)
project(maze_simulation_template C)

set(CMAKE_C_STANDARD 99)

add_library(${PROJECT_NAME} library.c library.h)
