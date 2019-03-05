#ifndef GMATH_COMMON_H
#define GMATH_COMMON_H

#if defined(__x86_64__) || defined(__i386__)
#define GMATH_USE_SSE
#endif

#if defined(_MSC_VER)
#define GMATH_ALIGN(x) __declspec(align(x))
#elif defined(__clang__)
#define GMATH_ALIGN(x) __attribute__ ((aligned(x)))
#elif defined(__GNUC__)
#define GMATH_ALIGN(x) __attribute__ ((aligned(x)))
#endif

#define GMATH_INLINE static inline

#define GMATH_PI 3.14159265358979323846

#endif
