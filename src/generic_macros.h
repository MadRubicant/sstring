#ifndef GENERIC_MACROS_H
#define GENERIC_MACROS_H

#define _TOKENPASTE(x, y) x ## y

// This nets us 27 levels of macro recursion depth

#define _EMPTY()
#define _DEFER(id) id _EMPTY()
#define _OBSTRUCT(...) __VA_ARGS__ _DEFER(_EMPTY)()
#define _EXPAND(...) __VA_ARGS__

#define _EVAL2(...) __VA_ARGS__
#define _EVAL1(...) _EVAL2(_EVAL2(_EVAL2(__VA_ARGS__)))
#define _EVAL(...) _EVAL1(_EVAL1(_EVAL1(__VA_ARGS__)))

#define RAW_STRING(x) #x
#define STRING(x) RAW_STRING(x)

#endif
