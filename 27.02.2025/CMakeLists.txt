cmake_minimum_required(VERSION 3.15)

project(mainCpp LANGUAGES CXX)

set(frist_name first)
set(second_name second)
set(third_name third)
set(fourth_name fourth)

add_executable(${frist_name} first.cpp)
add_executable(${second_name} second.cpp)
add_executable(${third_name} third.cpp)
add_executable(${fourth_name} fourth.cpp)
target_compile_features(${frist_name} PRIVATE cxx_std_17)
target_compile_options(${frist_name} PRIVATE -Wall -Wextra -pedantic)

target_compile_features(${second_name} PRIVATE cxx_std_17)
target_compile_options(${second_name} PRIVATE -Wall -Wextra -pedantic)

target_compile_features(${third_name} PRIVATE cxx_std_17)
target_compile_options(${third_name} PRIVATE -Wall -Wextra -pedantic)

target_compile_features(${fourth_name} PRIVATE cxx_std_17)
target_compile_options(${fourth_name} PRIVATE -Wall -Wextra -pedantic)