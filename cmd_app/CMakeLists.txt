find_package(Threads REQUIRED)

find_library(WIRINGPI_LIBRARIES NAMES REQUIRED wiringPi)
find_package(PkgConfig)

set(Boost_USE_STATIC_LIBS ON)
pkg_search_module(CLI REQUIRED cli)
find_package(Boost REQUIRED COMPONENTS system)

include_directories(..)

add_executable(cmd_app
  main.cc
  menu.h
  menu.cc
)

target_include_directories(cmd_app PUBLIC
  ${CLI_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)
target_link_libraries(cmd_app
  ${WIRINGPI_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  ${CLI_LIBRARIES}
  ${Boost_LIBRARIES}
  motor
)
