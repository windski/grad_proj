
find_package(Threads REQUIRED)

# Link against wiringPi
find_library(WIRINGPI_LIBRARIES NAMES REQUIRED wiringPi)

include_directories(..)

add_executable(example0_basic example0_basic.cc)
add_executable(example1_basic example1_basic.c)

set(libs ${WIRINGPI_LIBRARIES} pthread motor)

target_link_libraries(example0_basic ${libs})
target_link_libraries(example1_basic ${libs})

