cmake_minimum_required(VERSION 3.15)

project(mainCpp LANGUAGES CXX)

set(executable_name main)

add_executable(${executable_name} main.cpp)
target_compile_features(${executable_name} PRIVATE cxx_std_17)
target_compile_options(${executable_name} PRIVATE -Wall -Wextra -pedantic)