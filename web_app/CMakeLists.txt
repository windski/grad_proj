find_library(CPPCMS NAMES REQUIRED cppcms)
find_library(BOOSTER NAMES REQUIRED booster)
find_package(Threads REQUIRED)

include_directories(..)

set(templates page.tmpl)

add_custom_command(
  OUTPUT ${CMAKE_SOURCE_DIR}/web_app/page.cc
  COMMAND cppcms_tmpl_cc ${CMAKE_SOURCE_DIR}/web_app/${templates}
    -o ${CMAKE_SOURCE_DIR}/web_app/page.cc
  DEPENDS ${templates}
)

add_executable(app
  app.cc
  main.cc
  page.cc
)

target_link_libraries(app
  ${CPPCMS}
  ${BOOSTER}
  ${CMAKE_THREAD_LIBS_INIT}
  ${WIRINGPI_LIBRARIES}
  motor
)

file(COPY ${CMAKE_SOURCE_DIR}/web_app/config.js DESTINATION ${CMAKE_BINARY_DIR}/web_app)

