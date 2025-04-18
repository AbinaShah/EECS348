cmake_minimum_required(VERSION 3.10)
project(Lab10)

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp calculator.cpp)
add_executable(tests tests/tests.cpp calculator.cpp)
target_link_libraries(tests gtest gtest_main pthread)