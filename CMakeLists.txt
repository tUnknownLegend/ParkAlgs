cmake_minimum_required(VERSION 3.21)
project(1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

file(GLOB SOURCES *.cpp *.h)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCES IGraph/IGraph.cpp ListGraph/ListGraph.cpp ArcGraph/ArcGraph.cpp MatrixGraph/MatrixGraph.cpp SetGraph/SetGraph.cpp)
set(HEADERS IGraph/IGraph.h ListGraph/ListGraph.h ArcGraph/ArcGraph.h MatrixGraph/MatrixGraph.h SetGraph/SetGraph.h)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})

add_executable(Tests ${SOURCES} ${HEADERS} tests.cpp)

target_link_libraries(Tests GTest::Main)