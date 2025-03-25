cmake_minimum_required(VERSION 3.15)

project(mainCpp LANGUAGES CXX)

set(quick_sum quick_sum)

add_executable(${quick_sum} 
                quick_sum.cpp
                heap.cpp)