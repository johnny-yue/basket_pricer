cmake_minimum_required (VERSION 3.1.0)
set(CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 20)

project(basket_pricer VERSION 0.1.0)

add_executable(basket_pricer data_source.hpp market_data.hpp pricer.hpp tick_gen.hpp main.cpp)