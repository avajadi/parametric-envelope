cmake_minimum_required(VERSION 3.17)
project(parametric_envelope)

set(CMAKE_CXX_STANDARD 14)

include_directories(examples)
include_directories(include)
include_directories(src)

add_executable(parametric_envelope
        examples/src/example.cpp
        include/ParametricEnvelope.h
        include/Timer.h
        src/ParametricEnvelope.cpp
        src/Timer.cpp)
