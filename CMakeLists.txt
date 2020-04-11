cmake_minimum_required(VERSION 3.5)
project(MotorDriver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Include headers
add_subdirectory(lib)
add_subdirectory(examples)
add_subdirectory(cmd_app)

