#ifndef SSTRING_H
#define SSTRING_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>


const char* sstring_alloc(const char* string_lit, int len) {
  // Alloc 4 bytes more than we need
  void* buf = malloc(len + sizeof(int32_t));
  // If we're in an OOM condition, assert false
  if (buf == NULL)
    assert(0);
  
  
  // We're storing the size of the string in the 4 bytes before it
  int* size_loc = buf;
  char* str_loc = buf;
  str_loc += sizeof(int);
  
  *size_loc = len;
  strncpy(str_loc, string_lit, len);
  
  return str_loc;
}

int sstring_len(const char* sstring) {
  if (!sstring)
    return 0;
  return *(((int*)sstring) - 1);
}

const char* sstring_substr(const char* sstring, int start, int end) {
  int len = sstring_len(sstring);
  if (end > len)
    end = len;
  
}  
  
#endif
