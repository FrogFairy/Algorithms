cmake_minimum_required(VERSION 3.15)

project(mainCpp LANGUAGES CXX)

set(first first)
set(second second)
set(third third)
set(fourth fourth)

add_executable(${first} first.cpp)

add_executable(${second} 
second.cpp)

add_executable(${third} 
third.cpp)

add_executable(${fourth} 
fourth.cpp)