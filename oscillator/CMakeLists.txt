cmake_minimum_required(VERSION 3.4)
project(oscillator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        oscillator.cpp
        ../integrator/integrationMethods.cpp)

add_executable(oscillator ${SOURCE_FILES})