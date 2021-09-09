cmake_minimum_required(VERSION 3.17)
project(maze_simulation_template C)

set(CMAKE_C_STANDARD 99)

link_directories(lib)
add_executable(${PROJECT_NAME} main.c interface.c interface.h)
target_link_libraries(${PROJECT_NAME} libvenv_driver.a)
