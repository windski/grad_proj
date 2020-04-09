#ifndef LIB_CARRAY_H_
#define LIB_CARRAY_H_

#include <stdint.h>

#define CARRAY_LEN 4

#define carray_size(arr) ((arr)->len + 1)
#define cmatrix_size(m) ((m)->len + 1)

typedef struct carray {
  int64_t *data;
  int len;
  int capacity;
} carray_t;

typedef struct cmatrix {
  carray_t **array;
  int len;
  int capacity;
} cmatrix_t;

extern carray_t *carray_init();
extern void carray_destroy(carray_t *);
extern void carray_append(carray_t *, int64_t);
extern int64_t carray_index(carray_t *, int);

extern cmatrix_t *cmatrix_init();
extern void cmatrix_destroy(cmatrix_t *);
extern void cmatrix_append(cmatrix_t *, carray_t *);
extern carray_t *cmatrix_index(cmatrix_t *, int);

#endif  // LIB_CARRAY_H_
