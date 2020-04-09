set(LIB_SRC
  motor.cc
  motor.h
  cmotor.c
  cmotor.h
  carray.c
  carray.h
)


add_library(motor STATIC ${LIB_SRC})

