#include <stdio.h>

#include "sstring.h"


int main(int argc, char** argv) {
  for (int i = 0; i < argc; i++) {
    const char* str = sstring_alloc(argv[i], strlen(argv[i]));
    printf("%s: %d\n", str, sstring_len(str));
  }
}
