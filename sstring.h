#ifndef SSTRING_H
#define SSTRING_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>
#include <math.h>

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

static const char* sstring_alloc(const char* string, uint32_t len);
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

const char* sstring_cat(const char* left, const char* right); 



#endif
