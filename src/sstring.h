#ifndef SSTRING_H
#define SSTRING_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

//static const char* sstring_alloc(const char* string, uint32_t len, uint32_t bufsize);
const char* sstring_create(const char* bytestring);

const char* sstring_cpy(const char* sstring);

// You'd better not pass this function a string literal
// If you do have fun with your memory being scribbled over
void sstring_free(const char* sstring);

uint32_t sstring_len(const char* sstring);

const char* sstring_substr(const char* sstring, uint32_t start, uint32_t end);

// Compares two sstrings
int sstring_cmp(const char* a, const char* b); 

// Compares to sstrings for equality
int sstring_eq(const char* a, const char* b);

// Appends two sstrings, returning a new one
const char* sstring_append(const char* orig, const char* appstr);
// Appends a string literal to an sstring
const char* sstring_litcat(const char* orig, const char* strlit);
// Inserts one sstring into another at the specified position
const char* sstring_insert(const char* sstring, int pos, const char* insert);
// Inserts a string literal into an sstring
const char* sstring_litinsert(const char* sstring, int pos, const char* insert);

// Returns a NULL terminated array of sstrings
const char** sstring_split(const char* sstring, char splitchr, int* numsplit);
  /*
int sstring_find(const char* sstring, const char* strtofind);
int sstring_find_lit(const char* sstring, const char* strlit);*/
  // In an out of memory condition, these functions segfault
#ifdef SSTRING_DESTRUCTIVE
inline const char* sstring_d_append(const char* original, const char* append);
inline const char* sstring_d_insert(const char* original, const char* insert);
#endif
#ifdef __cplusplus
}
#endif
#endif
