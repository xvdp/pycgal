cmake_minimum_required(VERSION 3.10)
project(pycgal)

find_package(CGAL)


if ( CGAL_FOUND )
    add_subdirectory(pybind11)
    pybind11_add_module(pycgal src/main.cpp src/optimal_transport.cpp)

    target_link_libraries(pycgal PRIVATE CGAL::CGAL)

else()
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
endif()