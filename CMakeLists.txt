cmake_minimum_required(VERSION 3.10)

project(Coordinator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(modules/comm)
find_package(Boost REQUIRED COMPONENTS filesystem system)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Coordinator main.cpp ${SOURCES})
target_link_libraries(Coordinator PRIVATE Comm Boost::boost Boost::filesystem Boost::system)