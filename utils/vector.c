#include <stdio.h>
#include <stdlib.h>

// Define a struct to represent a dynamic array (vector)
typedef struct {
  int *data;       // Pointer to the array of integers
  size_t size;     // Current number of elements
  size_t capacity; // Maximum number of elements before resizing
} Vector;

// Initialize the vector
void v_init(Vector *vec) {
  vec->data = NULL;
  vec->size = 0;
  vec->capacity = 0;
}

void v_push(Vector *vec, int value) {
  if (vec->size == vec->capacity) {
    vec->capacity = (vec->capacity == 0) ? 1 : vec->capacity * 2;
    vec->data = realloc(vec->data, vec->capacity * sizeof(int));
    if (!vec->data) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }
  }
  vec->data[vec->size] = value;
  vec->size++;
}

int v_get(Vector *vec, size_t index) {
  if (index >= vec->size) {
    fprintf(stderr, "Index out of bounds\n");
    exit(EXIT_FAILURE);
  }
  return vec->data[index];
}

void v_memfree(Vector *vec) {
  free(vec->data);
  vec->data = NULL;
  vec->size = 0;
  vec->capacity = 0;
}
