#ifndef WANBEIYU_COMPAT_H
#define WANBEIYU_COMPAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>

typedef unsigned char wanbeiyu_uint8_t;
#define WANBEIYU_UINT8_MAX ((wanbeiyu_uint8_t)0xFF)

#if USHRT_MAX == 0xFFFF
typedef unsigned short wanbeiyu_uint16_t;
#elif UINT_MAX == 0xFFFF
typedef unsigned int wanbeiyu_uint16_t;
#elif ULONG_MAX == 0xFFFF
typedef unsigned long wanbeiyu_uint16_t;
#else
#error "16-bit unsigned integer type is not available on this platform."
#endif
#define WANBEIYU_UINT16_MAX ((wanbeiyu_uint16_t)0xFFFF)

#if SHRT_MIN <= -255 && SHRT_MAX >= 255
typedef short wanbeiyu_int_t;
#elif INT_MIN <= -255 && INT_MAX >= 255
typedef int wanbeiyu_int_t;
#elif LONG_MIN <= -255 && LONG_MAX >= 255
typedef long wanbeiyu_int_t;
#else
#error                                                                         \
    "Integer type that can hold values from -255 to 255 is not available on this platform."
#endif

typedef enum wanbeiyu_bool_t { WANBEIYU_FALSE, WANBEIYU_TRUE } wanbeiyu_bool_t;

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_COMPAT_H */