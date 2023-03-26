cmake_minimum_required (VERSION 3.8)

project(sim_module)
include(../../../common.cmake)

include_directories(../../../code/include/simulator/)
include_directories(../../../)

message(STATUS "adding simulator library")
add_library(simulator_lib simulator.cpp)
message(STATUS "simulator library added")

add_executable(simulator main.cpp)
#target_link_libraries(simulator simulator_lib)
message(STATUS "added executable simulator")
install(TARGETS simulator DESTINATION simulator)
message(STATUS "installing target done")