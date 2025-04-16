cmake_minimum_required(VERSION 3.15)

project(mainCpp LANGUAGES CXX)

set(coeval coeval)
set(first_k_elems first_k_elems)
# set(database database)

add_executable(${coeval}
                coeval.cpp)

add_executable(${first_k_elems} 
                first_k_elems.cpp)

# add_executable(${database} 
#                 database.cpp)