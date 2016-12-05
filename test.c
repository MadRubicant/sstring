#include <stdio.h>

#include "sstring.h"


int main(int argc, char** argv) {
  char* testa = "foo bar";
  char* testb = "bar baz";
  const char* test_eqa = sstring_create("foo");
  const char* test_eqb = sstring_create("bar");
  const char* test_eqc = sstring_create("foo");
  printf("A == B: %d\n", sstring_cmp(test_eqa, test_eqb));
  printf("B == C: %d\n", sstring_cmp(test_eqb, test_eqc));
  printf("A == C: %d\n", sstring_cmp(test_eqa, test_eqc));
}
