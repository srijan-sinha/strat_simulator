cmake_minimum_required (VERSION 3.8)

project(modules)
include(../../common.cmake)

include_directories(../../)

add_subdirectory(simulator simulator)
#add_subdirectory(strategy strategy)