cmake_minimum_required(VERSION 3.4)
project(integrator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    integrator.cpp
        integrationMethods.h integrationMethods.cpp)

add_executable(integrator ${SOURCE_FILES})
