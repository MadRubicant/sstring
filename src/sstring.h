#ifndef SSTRING_H
#define SSTRING_H

#define EXTERN_C extern "C" {
#define END_EXTERN_C }

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#ifdef __cplusplus
EXTERN_C
#endif
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

// Error codes
#define SSTRING_SUCCESS 0
#define SSTRING_BADALLOC -1
#define SSTRING_NULLARG -2
#define SSTRING_BOUNDSERROR -3

// ALL OPERATIONS ON A SAFE STRING THAT DON'T RETURN A NEW SAFE STRING ARE DESTRUCTIVE
// ALL LEFT-HAND ARGUMENTS TO FUNCTIONS WILL REMAIN VALID POINTERS
// HOWEVER, sstring->cstr MAY BE FREED BY
// sstring_cat
// sstring_append
// sstring_insert
// POSSIBLY MORE FUNCTIONS
// IF YOU NEED A STABLE POINTER, KEEP A sstring* INSTEAD OF THE CONTAINED BUFFER
typedef struct safe_string {
  char* cstr;
  size_t len;
} sstring;

sstring* sstring_create(const char* src);
void sstring_destroy(sstring* str);
int sstring_cat(sstring* src, const char* cat);
int sstring_append(sstring* src, sstring* append);
int sstring_insert(sstring* src, sstring* insert, size_t pos);
int sstring_equal(sstring* first, sstring* second);
int sstring_cmp(sstring* left, sstring* right);
sstring* sstring_copy(sstring* src);
sstring* sstring_substr(sstring* src, size_t start, size_t stop);
sstring** sstring_split(sstring* src, char splitchr, int* numsplit);
int sstring_contains(sstring* src, const char* cstr);

#ifdef __cplusplus
END_EXTERN_C
#endif
#endif
