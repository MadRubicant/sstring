#include <stdio.h>

#define POINTER_TYPE char
#include "generic_pointer.h"
#undef POINTER_TYPE

#define ARRAY_IMPLMENTATION

//#define ARRAY_TYPE char
//#include "generic_array.h"
//#undef ARRAY_TYPE

//#define ARRAY_TYPE array(char)
//#include "generic_array.h"
//#undef ARRAY_TYPE

#define ARRAY_TYPE POINTER(char)
#include "generic_array.h"
#undef ARRAY_TYPE

#undef ARRAY_IMPLENTATION

//typedef ARRAY(ARRAY(char*)) c_window;

int main(int argc, char** argv) {
  printf("Char called: %s\n", STRING(char));
  printf("Pointer to char called: %s\n", STRING(POINTER(char)));
  printf("Array of Pointers to char called: %s\n", STRING(array(POINTER(char))));
}
