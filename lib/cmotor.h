#ifndef LIB_CMOTOR_H_
#define LIB_CMOTOR_H_

#include <stdbool.h>
#include <pthread.h>
#include <wiringPi.h>
#include "carray.h"

#define PINS_NUM 4

#ifdef __cplusplus
extern "C" {
#endif

typedef struct motor {
  carray_t *pins;
  cmatrix_t *value;
  int delay;
  pthread_mutex_t mutex;
  pthread_t m_tid;
  bool is_stop;
  bool is_reverse;
} motor_t;


motor_t *motor_init(int a, int b, int c, int d);
void motor_destroy(motor_t *);
void motor_run(motor_t *, bool);
void motor_stop(motor_t *);

#ifdef __cplusplus
}
#endif

#endif  // LIB_CMOTOR_H_
