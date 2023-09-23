#ifndef INTEGERS_H
#define INTEGERS_H


#include <stdint.h>
#include <inttypes.h>


typedef  int_fast32_t i32;
typedef  int_fast64_t i64;
typedef uint_fast64_t u64;


#define  I32_MAX  INT_FAST32_MAX
#define  I64_MAX  INT_FAST64_MAX
#define UI64_MAX UINT_FAST64_MAX
#define  I32_MIN  INT_FAST32_MIN
#define  I64_MIN  INT_FAST64_MIN


#ifdef PRIi32
#undef PRIi32
#endif

#ifdef PRIi64
#undef PRIi64
#endif

#ifdef PRIu64
#undef PRIu64
#endif

#ifdef SCNi32
#undef SCNi32
#endif

#ifdef SCNi64
#undef SCNi64
#endif

#ifdef SCNu64
#undef SCNu64
#endif


#define PRIi32 PRIdFAST32
#define PRIi64 PRIdFAST64
#define PRIu64 PRIuFAST64

#define SCNi32 SCNdFAST32
#define SCNi64 SCNdFAST64
#define SCNu64 SCNuFAST64


#endif
