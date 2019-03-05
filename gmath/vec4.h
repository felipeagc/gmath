#ifndef GMATH_VEC4_H
#define GMATH_VEC4_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "types.h"

GMATH_INLINE vec4_t vec4_zero() { return (vec4_t){0.0f, 0.0f, 0.0f, 0.0f}; }

GMATH_INLINE vec4_t vec4_one() { return (vec4_t){1.0f, 1.0f, 1.0f, 1.0f}; }

// @TESTED
GMATH_INLINE vec4_t vec4_add(vec4_t left, vec4_t right) {
  vec4_t result;
#ifdef GMATH_USE_SSE
  _mm_store_ps(
      (float *)&result,
      _mm_add_ps(_mm_load_ps((float *)&left), _mm_load_ps((float *)&right)));
#else
  result.x = left.x + right.x;
  result.y = left.y + right.y;
  result.z = left.z + right.z;
  result.w = left.w + right.w;
#endif
  return result;
}

// @TESTED
GMATH_INLINE vec4_t vec4_mul(vec4_t left, vec4_t right) {
  vec4_t result;
#ifdef GMATH_USE_SSE
  _mm_store_ps(
      (float *)&result,
      _mm_mul_ps(_mm_load_ps((float *)&left), _mm_load_ps((float *)&right)));
#else
  result.x = left.x * right.x;
  result.y = left.y * right.y;
  result.z = left.z * right.z;
  result.w = left.w * right.w;
#endif
  return result;
}

GMATH_INLINE vec4_t vec4_muls(vec4_t left, float right) {
  return vec4_mul(left, (vec4_t){right, right, right, right});
}

// @TESTED
GMATH_INLINE float vec4_dot(vec4_t left, vec4_t right) {
  float result;
#ifdef GMATH_USE_SSE
  __m128 rone = _mm_mul_ps(*((__m128 *)&left), *((__m128 *)&right));
  __m128 rtwo = _mm_shuffle_ps(rone, rone, _MM_SHUFFLE(2, 3, 0, 1));
  rone = _mm_add_ps(rone, rtwo);
  rtwo = _mm_shuffle_ps(rone, rone, _MM_SHUFFLE(0, 1, 2, 3));
  rone = _mm_add_ps(rone, rtwo);
  _mm_store_ss(&result, rone);
#else
  result = (left.x * right.x) + (left.y * right.y) + (left.z * right.z) +
           (left.w * right.w);
#endif
  return result;
}

#ifdef __cplusplus
}
#endif

#endif
