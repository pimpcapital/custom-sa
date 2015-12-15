cmake_minimum_required(VERSION 2.6)

include_directories(include)
configure_file(resources/acserv.cf ${CMAKE_CURRENT_BINARY_DIR}/acserv.cf COPYONLY)
file(GLOB_RECURSE SRC_FILES *.c)
add_executable(saac ${SRC_FILES})
target_link_libraries(saac mysqlclient)