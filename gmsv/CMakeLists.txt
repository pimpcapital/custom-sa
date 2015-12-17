cmake_minimum_required(VERSION 2.6)

configure_file(resources/log.cf ${CMAKE_CURRENT_BINARY_DIR}/log.cf COPYONLY)
configure_file(resources/setup.cf ${CMAKE_CURRENT_BINARY_DIR}/setup.cf COPYONLY)

include_directories(src/include)
file(GLOB_RECURSE HEADER_FILES src/include/*.h)
file(GLOB_RECURSE SOURCE_FILES src/*.c)
add_executable(gmsv ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(gmsv m)