cmake_minimum_required(VERSION 3.15)

project(mainCpp LANGUAGES CXX)

set(merge merge)
set(remove remove)
set(simplify_path simplify_path)
set(trapping trapping)
set(largest largest)

add_executable(${merge} merge_two_sorted.cpp)
add_executable(${remove} remove_duplicates.cpp)
add_executable(${simplify_path} simplify_path.cpp)
add_executable(${trapping} trapping_rain_water.cpp)
add_executable(${largest} largest_rectangle.cpp)