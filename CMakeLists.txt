cmake_minimum_required(VERSION 3.5)
project(MotorDriver)

set(CMAKE_CXX_STANDARD 14)
if (CMAKE_BUILD_TYPE MATCHES "Debug")
  set(CMAKE_VERBOSE_MAKEFILE ON)
else()
  set(CMAKE_VERBOST_MAKEFILE OFF)
endif()

add_subdirectory(lib)
add_subdirectory(examples)
add_subdirectory(web_app)
add_subdirectory(cmd_app)

