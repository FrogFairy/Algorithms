cmake_minimum_required(VERSION 3.15)

project(1_seminar LANGUAGES CXX)

set(executable_name 1_seminar)

add_executable(${executable_name} 1_seminar/main.cpp)
target_compile_features(${executable_name} PRIVATE cxx_std_17)
target_compile_options(${executable_name} PRIVATE -Wall -Wextra -pedantic)