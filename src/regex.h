#ifndef SSTRING_REGEX_H
#define SSTRING_REGEX_H

#include "sstring.h"
#include <stdlib.h>


typedef struct sstring_regex sstring_regex;

sstring_regex* regex_compile(const char* pattern);


#endif
 
