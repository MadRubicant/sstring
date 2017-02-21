#include "generic_macros.h"

#define POINTER(T) _TOKENPASTE(_pointer_, T)

#ifdef POINTER_TYPE
typedef POINTER_TYPE* POINTER(POINTER_TYPE);
#endif

