cmake_minimum_required(VERSION 3.10)

project(Coordinator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(modules/comm)

add_executable(Coordinator main.cpp)
target_link_libraries(Coordinator PRIVATE Comm)