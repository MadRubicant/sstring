#include "generic_macros.h"


#define array(T) _EVAL(_TOKENPASTE(_array_, T))
#define array_push(T) _EVAL(_TOKENPASTE(_array_push_, T))
#define array_insert(T) _EVAL(_TOKENPASTE(_array_insert_, T))
#define array_search(T) _EVAL(_TOKENPASTE(_array_search_, T))
#define array_delete(T) _EVAL(_TOKENPASTE(_array_delete_, T))
#define array_free(T) _EVAL(_TOKENPASTE(_array_free_, T))
#define _array_grow(T) _EVAL(_TOKENPASTE(_array_grow_, T))
#define array_alloc(T) _EVAL(_TOKENPASTE(_array_alloc_, T))
#define _array_shrink(T) _EVAL(_TOKENPASTE(_array_shrink_, T))
#define array_clear(T) _EVAL(_TOKENPASTE(_array_clear, T))

#define ARRAY_SCALING 1.5
//#define ARRAY_TYPE int

#ifdef ARRAY_TYPE

#include <stdint.h>
#include <stdlib.h>

typedef struct array(ARRAY_TYPE) array(ARRAY_TYPE);
array(ARRAY_TYPE)* array_alloc(ARRAY_TYPE)(size_t init_size);
size_t array_push(ARRAY_TYPE)(array(ARRAY_TYPE)* arr, ARRAY_TYPE data);
size_t array_insert(ARRAY_TYPE)(array(ARRAY_TYPE)* arr, ARRAY_TYPE data, size_t location);
int array_search(ARRAY_TYPE)(array(ARRAY_TYPE)* arr, ARRAY_TYPE data);
size_t array_delete(ARRAY_TYPE)(array(ARRAY_TYPE)* arr, ARRAY_TYPE data);
void array_free(ARRAY_TYPE)(array(ARRAY_TYPE)* arr);
static void _array_grow(ARRAY_TYPE)(array(ARRAY_TYPE)* arr);
static void _array_shrink(ARRAY_TYPE)(array(ARRAY_TYPE)* arr);
void array_clear(ARRAY_TYPE)(array(ARRAY_TYPE)* arr);

#ifdef ARRAY_IMPLEMENTATION

typedef struct array(ARRAY_TYPE) {
  ARRAY_TYPE* data;
  size_t length;
  size_t capacity;
} array(ARRAY_TYPE);

array(ARRAY_TYPE)* array_alloc(ARRAY_TYPE)(size_t init_size) {
  array(ARRAY_TYPE)* arr = malloc(sizeof array(ARRAY_TYPE));
  arr->data = malloc(sizeof(ARRAY_TYPE) * init_size);
  arr->length = 0;
  arr->capacity = init_size;
}

size_t array_push(ARRAY_TYPE)(array(ARRAY_TYPE)* arr, ARRAY_TYPE data) {
  size_t push_loc = arr->length;
  if (push_loc >= arr->capacity)
    _array_grow(ARRAY_TYPE)(arr);
  arr->data[push_loc] = data;
  arr->length++;
  return push_loc;
};


size_t array_insert(ARRAY_TYPE)(array(ARRAY_TYPE)* arr, ARRAY_TYPE data, size_t location) {
  if (arr->length + 1 >= arr->capacity) {
    _array_grow(ARRAY_TYPE)(arr);
  }
  if (location >= arr->length)
    return array_push(ARRAY_TYPE)(arr, data);
  
  for (size_t i = arr->length; i > location; i--) {
    arr->data[i] = arr->data[i - 1];
  }
  arr->data[location] = data;
  return location;
};


size_t array_delete(ARRAY_TYPE)(array(ARRAY_TYPE)* arr, ARRAY_TYPE data) {
  for (int i = 0; i < arr->length; i++) {
    if (arr->data[i] == data) {
      for (int j = i; j < arr->length - 1; j++) {
	arr->data[j] = arr->data[j + 1];
      }
      arr->length--;
      break;
    }
  }
  if ((float)arr->length / arr->capacity < .5) {
    _array_shrink(ARRAY_TYPE)(arr);
  }
};


void array_free(ARRAY_TYPE)(array(ARRAY_TYPE)* arr) {
  free(arr->data);
  free(arr);
};


int array_search(ARRAY_TYPE)(array(ARRAY_TYPE)* arr, ARRAY_TYPE data) {
  for (int i = 0; i < arr->length; i++) {
    if (arr[i] == data)
      return i;
  }
  return -1;
};


static void _array_grow(ARRAY_TYPE)(array(ARRAY_TYPE)* arr) {
  size_t newlen = (size_t)(arr->capacity * ARRAY_SCALING);
  ARRAY_TYPE* newbuf = malloc(sizeof(ARRAY_TYPE) * newlen);
  for (size_t i = 0; i < arr->length; i++) {
    newbuf[i] = arr->data[i];
  }
  free(arr->data);
  arr->data = newbuf;
  arr->capacity = newlen;
};


static void _array_shrink(ARRAY_TYPE)(array(ARRAY_TYPE)* arr) {
  size_t newlen = (size_t)(arr->capacity / ARRAY_SCALING);
  ARRAY_TYPE* newbuf = malloc(sizeof(ARRAY_TYPE * newlen));
  for (size_t i = 0; i < arr->length; i++) {
    newbuf[i] = arr->data[i];
  }
  free(arr->data);
  arr->data = newbuf;
  arr->capacity = newlen;
};


void array_clear(ARRAY_TYPE)(array(ARRAY_TYPE)* arr) {
  arr->length = 0;
};


#endif
#endif
