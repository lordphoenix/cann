cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(cann)

add_executable(
    cann
    src/matrix.cc
    src/Neuron.cc
    src/Layer.cc
    src/NeuralNetwork.cc
)
