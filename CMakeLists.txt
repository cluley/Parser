cmake_minimum_required(VERSION 3.22.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(ini_parser)

add_executable(ini_configs_parse main.cpp file.ini parser.h parser.cpp file.ini)