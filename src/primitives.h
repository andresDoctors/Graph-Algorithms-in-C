#ifndef PRIMITIVES_H
#define PRIMITIVES_H


#include <stdint.h>
#include <inttypes.h>


typedef char* string;

typedef int8_t  i08;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u08;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;
typedef long double f128;


#define i08_MAX 0x7F
#define i16_MAX 0x7FFF
#define i32_MAX 0x7FFFFFFF
#define i64_MAX 0x7FFFFFFFFFFFFFFF

#define i08_MIN 0x80
#define i16_MIN 0x8000
#define i32_MIN 0x80000000
#define i64_MIN 0x8000000000000000

#define u08_MAX 0xFF
#define u16_MAX 0xFFFF
#define u32_MAX 0xFFFFFFFF
#define u64_MAX 0xFFFFFFFFFFFFFFFF

#define i08_PRI "%" PRId8
#define i16_PRI "%" PRId16
#define i32_PRI "%" PRId32
#define i64_PRI "%" PRId64

#define i08_SCN "%" SCNd8
#define i16_SCN "%" SCNd16
#define i32_SCN "%" SCNd32
#define i64_SCN "%" SCNd64

#define u08_PRI "%" PRIu8
#define u16_PRI "%" PRIu16
#define u32_PRI "%" PRIu32
#define u64_PRI "%" PRIu64

#define u08_SCN "%" SCNu8
#define u16_SCN "%" SCNu16
#define u32_SCN "%" SCNu32
#define u64_SCN "%" SCNu64

#define f32_PRI  "%f"
#define f64_PRI  "%lf"
#define f128_PRI "%Lf"

#define f32_SCN  "%f"
#define f64_SCN  "%lf"
#define f128_SCN "%Lf"


#endif
