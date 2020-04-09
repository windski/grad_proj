#include <stdio.h>
#include <unistd.h>
#include "lib/cmotor.h"

int main(void) {
  if (wiringPiSetup() == -1) {
    fprintf(stderr, "wiringPi setup failure\n");
    return -1;
  }

  motor_t *m = motor_init(0, 1, 2, 3);
  pthread_t pid = motor_run(m, false);
  sleep(3);
  motor_stop(m);
  pthread_join(pid, NULL);

  // reverse
  pid = motor_run(m, true);
  sleep(3);
  motor_stop(m);
  pthread_join(pid, NULL);

  motor_destroy(m);

  return 0;
}

