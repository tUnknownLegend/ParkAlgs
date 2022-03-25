cmake_minimum_required(VERSION 3.21)
project(2)

set(SOURCE_FILES 2.cpp)

add_executable(2 ${SOURCE_FILES})

add_subdirectory(tests)

target_link_libraries(2)