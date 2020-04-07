cmake_minimum_required(VERSION 3.5)
project(MotorDriver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)
find_package(Threads REQUIRED)

# Include headers
include_directories(.)

add_executable(MotorDriver
  main.cc
  motor.cc
)

# Link against wiringPi
find_library(WIRINGPI_LIBRARIES NAMES REQUIRED wiringPi)
target_link_libraries(MotorDriver
  ${WIRINGPI_LIBRARIES}
  pthread
)
