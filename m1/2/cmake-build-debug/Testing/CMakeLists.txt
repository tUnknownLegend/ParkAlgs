cmake_minimum_required(VERSION 3.14)
project(2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${2_INCLUDE_DIRS} ${2_SRC_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${2_SRC_LIBRARIES} ${2_LIBRARIES} GTest::Main)
