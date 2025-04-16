cmake_minimum_required(VERSION 3.15)

project(mainCpp LANGUAGES CXX)

set(coeval coeval)
set(first_k_elems first_k_elems)
set(count_of_inversions count_of_inversions)

add_executable(${coeval}
                coeval.cpp)

add_executable(${first_k_elems} 
                first_k_elems.cpp)

add_executable(${count_of_inversions} 
                count_of_inversions.cpp)