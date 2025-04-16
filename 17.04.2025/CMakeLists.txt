cmake_minimum_required(VERSION 3.15)

project(mainCpp LANGUAGES CXX)

set(coeval coeval)
# set(polyline polyline)
# set(database database)

add_executable(${coeval}
                coeval.cpp)

# add_executable(${polyline} 
#                 polyline.cpp)

# add_executable(${database} 
#                 database.cpp)