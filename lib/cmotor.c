#include <assert.h>
#include <stdlib.h>
#include "cmotor.h"

motor_t *motor_init(int a, int b, int c, int d) {
  motor_t *m = (motor_t *)malloc(sizeof(motor_t));
  m->pins = carray_init();
  carray_append(m->pins, a);
  carray_append(m->pins, b);
  carray_append(m->pins, c);
  carray_append(m->pins, d);

  for (int i = 0; i < carray_size(m->pins); i++) {
    pinMode(carray_index(m->pins, i), OUTPUT);
  }

  m->value = cmatrix_init();
  for (int i = 0; i < PINS_NUM; i++) {
    carray_t *tmp = carray_init();
    for (int j = 0; j < PINS_NUM; j++) {
      if (i == j) {
        carray_append(tmp, HIGH);
      } else {
        carray_append(tmp, LOW);
      }
    }

    cmatrix_append(m->value, tmp);
  }
  m->delay = 2;
  m->is_stop = false;
  m->is_reverse = false;
  pthread_mutex_init(&(m->mutex), NULL);
  
  return m;
}

void motor_destroy(motor_t *m) {
  if (m != NULL) {
    if (m->pins != NULL) {
      carray_destroy(m->pins);
    }
    pthread_mutex_destroy(&(m->mutex));

    free(m);
  }
}


void write2pins(motor_t *m, int row) {
  assert(m != NULL);
  for (int i = 0; i < carray_size(m->pins); i++) {
    digitalWrite(carray_index(m->pins, i),
                 carray_index(cmatrix_index(m->value, row), i));
  }
}


static void *
thread_run(void *arg) {
  motor_t *m = (motor_t *)arg;
  if (m->is_stop) {
    pthread_mutex_lock(&(m->mutex));
    m->is_stop = false;
    pthread_mutex_unlock(&(m->mutex));
  }

  while (!m->is_stop) {
    if (m->is_reverse) {
      for (int i = 0; i < PINS_NUM; i++) {
        write2pins(m, i);
        delay(m->delay);
      }
    } else {
      for (int i = PINS_NUM - 1; i >= 0; i--) {
        write2pins(m, i);
        delay(m->delay);
      }
    }
  }

  return NULL;
}


pthread_t motor_run(motor_t *m, bool is_reverse) {
  assert(m != NULL);
  m->is_reverse = is_reverse;

  pthread_t pid;
  pthread_create(&pid, NULL, thread_run, m);
  return pid;
}

void motor_stop(motor_t *m) {
  assert(m != NULL);
  pthread_mutex_lock(&(m->mutex));
  m->is_stop = true;
  pthread_mutex_unlock(&(m->mutex));
}
