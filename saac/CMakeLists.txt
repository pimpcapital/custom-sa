cmake_minimum_required(VERSION 2.8)

file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
include_directories(src/include)
file(GLOB_RECURSE HEADER_FILES src/include/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.c)
add_executable(saac ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(saac mysqlclient)