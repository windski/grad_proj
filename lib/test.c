#include <stdio.h>
#include "carray.h"

int main(void) {
  carray_t *arr = carray_init();

  for (int i = 0; i < 100; i++) {
    carray_append(arr, i);
  }

  for (int i = 0; i < 100; i++) {
    printf("%lld ", carray_index(arr, i));
  }
  printf("\n");

  carray_destroy(arr);
  return 0;
}

