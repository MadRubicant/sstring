#ifndef SSTRINGIO_H
#define SSTRINGIO_H

#include "sstring.h"
#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
EXTERN_C
#endif

#define SSTRINGIO_INPUT_BUFSIZE 512

// Get a line from file and return it
sstring* sstring_getline(FILE* file);
// Load the entire contents of the file into memory. May interact poorly with stdin
// Also only works on linux
// TODO: Support win32 and darwin, and use a mmap scheme for large (>1 MB?) files
sstring* sstring_loadfile(FILE* file);

sstring* sstring_sprintf(const char* fmt, ...);

#ifdef __cplusplus
END_EXTERN_C
#endif 

#endif // SSTRINGIO_H
