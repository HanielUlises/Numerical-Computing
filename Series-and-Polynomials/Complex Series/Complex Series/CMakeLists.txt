cmake_minimum_required(VERSION 3.14)
project(ComplexSeriesApp)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt REQUIRED)

add_executable(ComplexSeriesApp main.cpp ComplexSeries.cpp)
target_link_libraries(ComplexSeriesApp PRIVATE fmt::fmt)
