cmake_minimum_required (VERSION 3.8)

project(utils)
include(../../../common.cmake)

include_directories(../../../code/include/utils/)
include_directories(../../../)

add_library(parser_lib parser.cpp)