#include <stdio.h>
#include "cmotor.h"
#include <unistd.h>

int main(void) {
  wiringPiSetup();
  motor_t *m = motor_init(0, 1, 2, 3);

  pthread_t pid = motor_run(m, true);
  sleep(10);
  motor_stop(m);

  pthread_join(pid, NULL);
  motor_destroy(m);
  return 0;
}

