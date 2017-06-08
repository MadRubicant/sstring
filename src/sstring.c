#include <stdio.h>
#include "sstring.h"


#define strmalloc malloc

sstring* sstring_alloc(size_t size) {
  assert(size >= 0);
  sstring* ret = strmalloc(sizeof(sstring));
  if (!ret)
    return NULL;
  
  ret->len = size;
  ret->cstr = strmalloc(size + 1); // Allocate one byte for trailing \0
  if (!ret->cstr) {
    free(ret);
    return NULL;
  }
  ret->cstr[size] = '\0';
  return ret;
}

sstring* sstring_create(const char* src) {
  size_t len = strlen(src);
  sstring* sstr = sstring_alloc(len);
  if (!sstr)
    return NULL;
  sstr->cstr[len] = '\0';
  for (size_t i = 0; i < len; i++) {
    sstr->cstr[i] = src[i];
  }
  return sstr;
}

void sstring_destroy(sstring* str) {
  free(str->cstr);
  free(str);
}

int sstring_cat(sstring* src, const char* cat) {
  if (!cat || !src)
    return SSTRING_NULLARG;
  size_t cat_size = src->len + strlen(cat) + 1;
  sstring* ret = sstring_alloc(cat_size);

  if (!ret)
    return SSTRING_BADALLOC;

  ret->cstr[cat_size] = '\0';
  for (size_t i = 0; i < src->len; i++)
    ret->cstr[i] = src->cstr[i];
  for (size_t i = src->len; i < cat_size; i++)
    ret->cstr[i] = src->cstr[i];
  
  sstring_destroy(src);
  *src = *ret;
  return 0;
}

int sstring_append(sstring* src, sstring* append) {
  if (!src || !append)
    return SSTRING_NULLARG;

  size_t final_size = src->len + append->len + 1;
  sstring* ret = sstring_alloc(final_size);

  if (!ret)
    return SSTRING_BADALLOC;

  strcpy(ret->cstr, src->cstr);
  strcpy(ret->cstr + src->len, append->cstr);
  sstring_destroy(src);
  *src = *ret;
  return 0;
}

int sstring_insert(sstring* src, sstring* insert, size_t pos) {
  if (!src || !insert)
    return SSTRING_NULLARG;

  size_t final_size = src->len + insert->len + 1;
  if (pos > final_size)
    return SSTRING_BOUNDSERROR;
  
  sstring* ret = sstring_alloc(final_size);

  if (!ret)
    return SSTRING_BADALLOC;

  ret->cstr[final_size] = '\0';

  for (size_t i = 0; i < pos; i++)
    ret->cstr[i] = src->cstr[i];
  for (size_t i = 0; i < insert->len; i++)
    ret->cstr[pos + i] = insert->cstr[i];
  for (size_t i = pos; i < src->len; i++)
    ret->cstr[pos + insert->len + i] = src->cstr[i];
  
  sstring_destroy(src);
  *src = *ret;
  return 0;
}


int sstring_equal(sstring* first, sstring* second) {
  if (!first || !second)
    return 0;
  if (first->len != second->len)
    return 0;
  for (size_t i = 0; i < first->len; i++) {
    if (first->cstr[i] != second->cstr[i])
      return 0;
  }
  return 1;
}

// Negative if left < right, zero if eql, positive if left > right
int sstring_cmp(sstring* left, sstring* right) {
  if (!left)
    return -1;
  if (!right)
    return 1;
  if (!left || !right)
    return 0;
  
  for (size_t i = 0; i < left->len && i < right->len; i++) {
    if (left->cstr[i] == right->cstr[i])
      continue;
    else
      return left->cstr[i] - right->cstr[i];
  }
  
  if (left->len != right->len)
    return left->len - right->len;
  return 0;
}

sstring* sstring_copy(sstring* src) {
  if (!src)
    return NULL;
  
  sstring* ret = sstring_alloc(src->len);
  if (!ret)
    return NULL;
  
  for (size_t i = 0; i < src->len; i++)
    ret->cstr[i] = src->cstr[i];

  return ret;
}

sstring* sstring_substr(sstring* src, size_t start, size_t stop) {
  if (!src)
    return NULL;
  if (start > stop || start == stop)
    return NULL;

  sstring* ret = sstring_alloc(stop - start);
  if (!ret)
    return NULL;
  
  for (size_t i = 0; i < stop - start; i++)
    ret->cstr[i] = src->cstr[start + i];

  return ret;
}

sstring** sstring_split(sstring* src, char splitchr, int* count) {
  if (!src)
    return NULL;
  
  // Scan the array for occurances of splitchr
  int numsplit = 0;
  for (size_t i = 0; i < src->len; i++)
    if (src->cstr[i] == splitchr)
      numsplit++;

  sstring** splitarr = strmalloc(sizeof(sstring**) * (numsplit + 1));
  if (!splitarr)
    return NULL;
  
  splitarr[numsplit] = NULL;

  size_t start_pos = 0;
  int cursplit = 0;
  for (size_t i = 0; i < src->len; i++) {
    if (src->cstr[i] == splitchr) {
      // If start_pos == i, that means one of
      // A. It's the first character
      // B. We split on the last character
      // C. The last character satisfied one of A, B, or C
      // In any of these cases, skip this character, move to the next,
      // and decrement the number of splits we have
      if (start_pos == i) {
	start_pos++;
	numsplit--;
	splitarr[numsplit] = NULL;
	continue;
      }
      
      sstring* sub = sstring_substr(src, start_pos, i);
      if (!sub)
	goto cleanup;
      splitarr[cursplit] = sub;
      cursplit++;
      start_pos = i + 1;
    }
  }
  
  *count = numsplit;
  return splitarr;
  
 cleanup:
  for (int i = 0; i < cursplit; i++)
    sstring_destroy(splitarr[i]);
  free(splitarr);
  *count = -1;
  return NULL;
}

int sstring_contains(sstring* src, const char* cstr) {
  if (!src || !cstr)
    return 0;
  
  size_t len = strlen(cstr);
  if (len < src->len)
    return 0;

  for (size_t i = 0; i < src->len; i++) {
    if(i + len > src->len)
      return 0;
    
    int found = 1;
    for (size_t j = 0; j < len; j++) {
      if (src->cstr[i + j] != cstr[j]) {
	found = 0;
	break;
      }
      if (found)
	return 1;
    }
  }
  return 0;
}
