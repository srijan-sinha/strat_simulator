cmake_minimum_required (VERSION 3.8)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/c++.cmake)

find_package(Boost 1.75 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})