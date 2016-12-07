# sstring
Single-header library for manipulating strings that know their own length


# Functions
| Name | Signature | Description |
| ---- | --------- | ----------- |
| sstring_create | const char* sstring_create(const char* string) | Allocates and returns a new sstring based on the given string literal |
| sstring_free | void sstring_free(const char\* sstring) | Frees an sstring. Passing this a const char\* not allocated with sstring_alloc is an error |
| sstring_len | uint32_t sstring_len(const char\* sstring) | Gives the length of the sstring. |
| sstring_substr | const char\* sstring_substr(const char\* sstring, uint32_t start, uint32_t end) | Creates a substring that starts at index start and goes until index end, noninclusive | 
| sstring_cmp | int sstring_cmp(const char\* a, const char\* b) | Equivalent to strcmp(a, b) |
| sstring_eq | int sstring_eq(const char\* a, const char\* b) | Compares the two sstrings for equality. If they consist of entirely the same characters, returns 1 |
| sstring_cat | const char\* sstring_cat(const char\* left, const char\* right) | Creates a new sstring composed of left.right |
| sstring_insert | const char\* sstring_insert(const char* sstring, int pos, const char* insert) | Inserts a string into sstring starting at pos, with the original string resuming afterwards |
| sstring_split | const char** sstring_split(const char* sstring, char splitchr, int* numsplit) | Splits sstring into a number of substrings delimited by splitchr; the number or arrays is stored in numsplit | 