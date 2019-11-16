cmake_minimum_required(VERSION 3.10)
project(pycgal)

message(STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})

add_subdirectory(pybind11)
include(cgal/CGALConfig.cmake)
pybind11_add_module(pycgal src/main.cpp src/optimal_transport.cpp)
target_link_libraries(pycgal PRIVATE CGAL::CGAL)