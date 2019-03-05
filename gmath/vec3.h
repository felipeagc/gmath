#ifndef GMATH_VEC3_H
#define GMATH_VEC3_H

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"
#include <math.h>

GMATH_INLINE vec3_t vec3_zero() { return (vec3_t){0.0f, 0.0f, 0.0f}; }

GMATH_INLINE vec3_t vec3_one() { return (vec3_t){1.0f, 1.0f, 1.0f}; }

// @TESTED
GMATH_INLINE vec3_t vec3_add(vec3_t left, vec3_t right) {
  vec3_t result;
  result.x = left.x + right.x;
  result.y = left.y + right.y;
  result.z = left.z + right.z;
  return result;
}

// @TODO: test
GMATH_INLINE vec3_t vec3_adds(vec3_t left, float right) {
  vec3_t result;
  result.x = left.x + right;
  result.y = left.y + right;
  result.z = left.z + right;
  return result;
}

// @TODO: test
GMATH_INLINE vec3_t vec3_sub(vec3_t left, vec3_t right) {
  vec3_t result;
  result.x = left.x - right.x;
  result.y = left.y - right.y;
  result.z = left.z - right.z;
  return result;
}

// @TODO: test
GMATH_INLINE vec3_t vec3_subs(vec3_t left, float right) {
  vec3_t result;
  result.x = left.x - right;
  result.y = left.y - right;
  result.z = left.z - right;
  return result;
}

// @TESTED
GMATH_INLINE vec3_t vec3_mul(vec3_t left, vec3_t right) {
  vec3_t result;
  result.x = left.x * right.x;
  result.y = left.y * right.y;
  result.z = left.z * right.z;
  return result;
}

// @TODO: test
GMATH_INLINE vec3_t vec3_muls(vec3_t left, float right) {
  vec3_t result;
  result.x = left.x * right;
  result.y = left.y * right;
  result.z = left.z * right;
  return result;
}

// @TODO: test
GMATH_INLINE vec3_t vec3_div(vec3_t left, vec3_t right) {
  vec3_t result;
  result.x = left.x / right.x;
  result.y = left.y / right.y;
  result.z = left.z / right.z;
  return result;
}

// @TODO: test
GMATH_INLINE vec3_t vec3_divs(vec3_t left, float right) {
  vec3_t result;
  result.x = left.x / right;
  result.y = left.y / right;
  result.z = left.z / right;
  return result;
}

// @TESTED
GMATH_INLINE float vec3_dot(vec3_t left, vec3_t right) {
  return (left.x * right.x) + (left.y * right.y) + (left.z * right.z);
}

// @TODO: test
GMATH_INLINE vec3_t vec3_cross(vec3_t left, vec3_t right) {
  vec3_t result;
  result.x = (left.y * right.z) - (left.z * right.y);
  result.y = (left.z * right.x) - (left.x * right.z);
  result.z = (left.x * right.y) - (left.y * right.x);
  return result;
}

// @TODO: test
// @TODO: make compatible with glm
// @TODO: test with zero norm vector
GMATH_INLINE vec3_t vec3_normalize(vec3_t vec) {
  vec3_t result = vec;
  float norm = sqrt(vec3_dot(vec, vec));
  if (norm != 0.0f) {
    result = vec3_muls(vec, 1.0f / norm);
  }
  return result;
}

#ifdef __cplusplus
}
#endif

#endif
