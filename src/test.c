#include <stdio.h>

#include "sstring.h"


int main(int argc, char** argv) {
  const char* testsplit = sstring_create("foo.bar.baz");
  int numsplit;
  const char** splits = sstring_split(testsplit, '.', &numsplit);
  for (int i = 0; i < numsplit; i++) {
    printf("String: %s\n", splits[i]);
  }
}
