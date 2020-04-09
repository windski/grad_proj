#include <assert.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "carray.h"

carray_t *carray_init() {
  carray_t *arr = (carray_t *)malloc(sizeof(carray_t));
  assert(arr != NULL);
  bzero(arr, sizeof(carray_t));

  arr->data = (int64_t *)malloc(sizeof(int64_t) * CARRAY_LEN);
  assert(arr->data != NULL);
  bzero(arr->data, sizeof(arr->data));
  arr->capacity = CARRAY_LEN;
  return arr;
}


void carray_destroy(carray_t *arr) {
  if (arr != NULL) {
    if (arr->data != NULL) {
      free(arr->data);
    }

    free(arr);
  }
}


void expand_capacity(carray_t *arr) {
  assert(arr != NULL);
  int64_t *tmp = (int64_t *)malloc(sizeof(int64_t) * arr->capacity * 2);
  assert(tmp != NULL);
  arr->capacity *= 2;
  memmove(tmp, arr->data, arr->len * sizeof(int64_t));
  free(arr->data);
  arr->data = tmp;
}


void carray_append(carray_t *arr, int64_t data) {
  assert(arr != NULL);
  if (arr->len == arr->capacity) {
    expand_capacity(arr);
  }

  arr->data[arr->len] = data;
  arr->len++;
}


int64_t carray_index(carray_t *arr, int idx) {
  assert(arr != NULL);
  assert(arr->len >= idx);
  return arr->data[idx];
}


cmatrix_t *cmatrix_init() {
  cmatrix_t *matrix = (cmatrix_t *)malloc(sizeof(cmatrix_t));
  assert(matrix != NULL);
  bzero(matrix, sizeof(cmatrix_t));
 
  matrix->array = (carray_t **)malloc(sizeof(carray_t *) * CARRAY_LEN);
  assert(matrix->array);
  matrix->capacity = CARRAY_LEN;
  return matrix;
}


void cmatrix_destroy(cmatrix_t *m) {
  if (m != NULL) {
    if (m->array != NULL) {
      free(m->array);
    }
    free(m);
  }
}


void expand_matrix_capacity(cmatrix_t *m) {
  assert(m != NULL);
  carray_t **tmp = (carray_t **)malloc(sizeof(carray_t *) * m->capacity * 2);
  assert(tmp != NULL);
  m->capacity *= 2;
  memmove(tmp, m->array, m->len * sizeof(carray_t *));
  free(m->array);
  m->array = tmp;
}

void cmatrix_append(cmatrix_t *m, carray_t *arr) {
  assert(m != NULL);
  if (m->len == m->capacity) {
    expand_matrix_capacity(m);
  }

  m->array[m->len] = arr;
  m->len++;
}

carray_t *cmatrix_index(cmatrix_t *m, int idx) {
  assert(m != NULL);
  assert(m->len >= idx);
  return m->array[idx];
}
