#include "sstring.h"
#include "stretchy_buffer.h"

const char* sstring_alloc(const char* string, uint32_t len, uint32_t bufsize) {
  // Alloc 4 bytes more than we need
  void* buf = malloc(bufsize + 1 + sizeof(int32_t));
  // If we're in an OOM condition, assert false
  if (buf == NULL)
    assert(0);
  
  
  // We're storing the size of the string in the 4 bytes before it
  int* size_loc = buf;
  char* str_loc = buf;
  str_loc += sizeof(uint32_t);
  
  *size_loc = bufsize;
  strncpy(str_loc, string, len);
  str_loc[len] = '\0';
  return str_loc;
}

const char* sstring_create(const char* bytestring) {
  if (bytestring) {
    return sstring_alloc(bytestring, strlen(bytestring), strlen(bytestring));;
  }
  return NULL;
}

const char* sstring_cpy(const char* sstring) {
  return sstring_alloc(sstring, sstring_len(sstring), sstring_len(sstring));
}

void sstring_free(const char* sstring) {
  char* base_addr = (char*)sstring - sizeof(uint32_t);
  free(base_addr);
}

uint32_t sstring_len(const char* sstring) {
  if (!sstring)
    return -1;
  return *((uint32_t*)(sstring - sizeof(uint32_t)));
}

const char* sstring_substr(const char* sstring, uint32_t start, uint32_t end) {
  int len = sstring_len(sstring);
  end = min(end, len);
  
  const char* start_loc = sstring + start;
  uint32_t sublen = end - start;
  const char* substring = sstring_alloc(start_loc, sublen, sublen);
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
  
  char* final = (char*)sstring_alloc(left, lena, lena + lenb);
  for (int i = 0; i < lenb; i++) {
    int strpos = i + lena;
    final[strpos] = right[i];
  }
  final[lena + lenb] = '\0';
  return final;
}

const char** sstring_split(const char* sstring, char splitchr, int* numsplit) {
  uint32_t start = 0;
  uint32_t len = sstring_len(sstring);
  const char** split_arr = NULL;
  
  for (int i = 0; i < len; i++) {
    if (sstring[i] == splitchr) {
      sb_push(split_arr, sstring_substr(sstring, start, start + i));
      start += i;
    }
  }
  *numsplit = sb_count(split_arr);
  
  const char** ret_arr = malloc(*numsplit * sizeof(char*));
  for (int i = 0; i < *numsplit - 1; i++) {
    ret_arr[i] = split_arr[i];
  }
  sb_free(split_arr);
  return ret_arr;
}

const char* sstring_insert(const char* sstring, int pos, const char* insert) {
  uint32_t lena = sstring_len(sstring);
  uint32_t lenb = sstring_len(insert);
  if (pos < lena)
    return NULL;
  
  char* ret = (char*)sstring_alloc("", 0, lena + lenb);
  for (uint32_t i = 0; i < pos; i++) {
    ret[i] = sstring[i];
  }
  for (uint32_t i = pos; i < lenb; i++) {
    ret[pos + i] = insert[i];
  }
  for (uint32_t i = pos; i < lena; i++) {
    ret[pos + lenb + i] = sstring[i];
  }

  return ret;
  
}
