

cmake_minimum_required (VERSION 2.6)
project (radar)


set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")
add_compile_options(-std=c++11)

add_subdirectory(sensor)



