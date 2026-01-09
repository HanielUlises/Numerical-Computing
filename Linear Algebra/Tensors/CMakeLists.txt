cmake_minimum_required(VERSION 3.14)
project(Tensors LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Eigen3 REQUIRED NO_MODULE)

add_executable(tensors
    main.cpp
)

target_include_directories(tensors PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(tensors PRIVATE Eigen3::Eigen)