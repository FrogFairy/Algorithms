cmake_minimum_required(VERSION 3.15)

project(mainCpp LANGUAGES CXX)

set(quick_sum quick_sum)
set(dead_ends dead_ends)
set(sliding_max sliding_max)

add_executable(${quick_sum} 
                quick_sum.cpp
                heap.cpp)

add_executable(${dead_ends} 
                dead_ends.cpp
                heap.cpp)

add_executable(${sliding_max} 
                sliding_max.cpp
                heap.cpp)