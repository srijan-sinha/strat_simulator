cmake_minimum_required (VERSION 3.8)

project(sim_module)
include(../../../common.cmake)

include_directories(${Boost_INCLUDE_DIR})
include_directories(../../../code/include/)
include_directories(../../../)

add_library(simulator_lib simulator.cpp)

add_executable(simulator main.cpp)
target_link_libraries(simulator simulator_lib parser_lib)

install(TARGETS simulator DESTINATION simulator)