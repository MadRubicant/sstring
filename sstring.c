#include "sstring.h"


const char* sstring_alloc(const char* string, uint32_t len) {
  // Alloc 4 bytes more than we need
  void* buf = malloc(len + 1 + sizeof(int32_t));
  // If we're in an OOM condition, assert false
  if (buf == NULL)
    assert(0);
  
  
  // We're storing the size of the string in the 4 bytes before it
  int* size_loc = buf;
  char* str_loc = buf;
  str_loc += sizeof(int);
  
  *size_loc = len;
  strncpy(str_loc, string, len);
  str_loc[len] = '\0';
  return str_loc;
}

const char* sstring_cpy(const char* sstring) {
  return sstring_alloc(sstring, sstring_len(sstring));
}

void sstring_free(const char* sstring) {
  char* base_addr = (char*)sstring - 4;
  free(base_addr);
}

uint32_t sstring_len(const char* sstring) {
  if (!sstring)
    return 0;
  return *(((uint32_t*)sstring) - 1);
}

const char* sstring_substr(const char* sstring, uint32_t start, uint32_t end) {
  int len = sstring_len(sstring);
  end = min(end, len);
  
  const char* start_loc = sstring + start;
  uint32_t sublen = end - start;
  const char* substring = sstring_alloc(start_loc, sublen);
  return substring;
}

int sstring_cmp(const char* a, const char* b) {
  uint32_t lena = sstring_len(a);
  uint32_t lenb = sstring_len(b);

  for (int i = 0; i < min(lena, lenb); i++){
    int diff = a[i] - b[i];
    if (diff)
      return diff;
  }

  return 0;
  
}

// Compares to sstrings for equality
int sstring_eq(const char* a, const char* b) {
  uint32_t lena = sstring_len(a);
  uint32_t lenb = sstring_len(b);
  for (int i = 0; i < min(lena, lenb); i++) {
    int diff = a[i] - b[i];
    if (diff)
      return 0;
  }
  return 1;
}

const char* sstring_cat(const char* left, const char* right) {
  uint32_t lena = sstring_len(left);
  uint32_t lenb = sstring_len(right);
  
  char* final = (char*)sstring_alloc(left, lena + lenb);
  for (int i = 0; i < lenb; i++) {
    int strpos = i + lena;
    final[strpos] = right[i];
  }
  final[lena + lenb] = '\0';
  return final;
}
