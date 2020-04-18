cmake_minimum_required(VERSION 3.13.4)
project(topsort)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

add_executable(topsort main.cpp)

target_link_libraries (topsort Boost::program_options)

