#ifndef GMATH_VEC2_H
#define GMATH_VEC2_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

GMATH_INLINE vec2_t vec2_zero() { return (vec2_t){0.0f, 0.0f}; }

GMATH_INLINE vec2_t vec2_one() { return (vec2_t){1.0f, 1.0f}; }

#ifdef __cplusplus
}
#endif

#endif
