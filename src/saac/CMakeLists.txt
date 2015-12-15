cmake_minimum_required(VERSION 2.6)

include_directories(include)
link_directories(/usr/lib64/mysql)


include_directories("${PROJECT_BINARY_DIR}")
add_executable(saac main.c)
