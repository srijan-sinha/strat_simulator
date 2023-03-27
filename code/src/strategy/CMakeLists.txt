cmake_minimum_required (VERSION 3.8)

project(utils)
include(../../../common.cmake)

include_directories(../../../code/include/strategy/)
include_directories(../../../)

add_library(sample_strategy_1_lib sample_strategy_1.cpp)
add_library(sample_strategy_2_lib sample_strategy_2.cpp)
add_library(strat_utils_lib strategy_utils.cpp)