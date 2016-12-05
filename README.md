# sstring
Single-header library for manipulating strings that know their own length


# Functions
| Name | Signature | Description |
| ---- | --------- | ----------- |
| sstring_alloc | const char* sstring_alloc(const char* string, uint32_t len) | Allocates and returns a new sstring, and initializes it to the parameter string |
| sstring_free | void sstring_free(const char\* sstring) | Frees an sstring. Passing this a const char\* not allocated with sstring_alloc is an error |
| sstring_len | uint32_t sstring_len(const char\* sstring) | Gives the length of the sstring. |
| sstring_substr | const char\* sstring_substr(const char\* sstring, uint32_t start, uint32_t end) | Creates a substring that starts at index start and goes until index end, noninclusive | 
| sstring_cmp | int sstring_cmp(const char\* a, const char\* b) | Equivalent to strcmp(a, b) |
| sstring_eq | int sstring_eq(const char\* a, const char\* b) | Compares the two sstrings for equality. If they consist of entirely the same characters, returns 1 |
| sstring_cat | const char\* sstring_cat(const char\* left, const char\* right) | Creates a new sstring composed of left.right |
