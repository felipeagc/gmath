#ifndef GMATH_MAT4_H
#define GMATH_MAT4_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "types.h"
#include "vec3.h"
#include "vec4.h"
#include <math.h>
#include <xmmintrin.h>

// @TESTED
GMATH_INLINE mat4_t mat4_zero() {
  return (mat4_t){{
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
  }};
}

// @TESTED
GMATH_INLINE mat4_t mat4_diagonal(float f) {
  return (mat4_t){{
      {f, 0, 0, 0},
      {0, f, 0, 0},
      {0, 0, f, 0},
      {0, 0, 0, f},
  }};
}

// @TESTED
GMATH_INLINE mat4_t mat4_identity() { return mat4_diagonal(1.0f); }

// @TESTED
GMATH_INLINE mat4_t mat4_transpose(mat4_t mat) {
  mat4_t result = mat;
#ifdef GMATH_USE_SSE
  _MM_TRANSPOSE4_PS(
      result.sse_columns[0],
      result.sse_columns[1],
      result.sse_columns[2],
      result.sse_columns[3]);
#else
  result.columns[0][1] = mat.columns[1][0];
  result.columns[0][2] = mat.columns[2][0];
  result.columns[0][3] = mat.columns[3][0];

  result.columns[1][0] = mat.columns[0][1];
  result.columns[1][2] = mat.columns[2][1];
  result.columns[1][3] = mat.columns[3][1];

  result.columns[2][0] = mat.columns[0][2];
  result.columns[2][1] = mat.columns[1][2];
  result.columns[2][3] = mat.columns[3][2];

  result.columns[3][0] = mat.columns[0][3];
  result.columns[3][1] = mat.columns[1][3];
  result.columns[3][2] = mat.columns[2][3];
#endif
  return result;
}

// @TESTED
GMATH_INLINE mat4_t mat4_add(mat4_t left, mat4_t right) {
  mat4_t result;
#ifdef GMATH_USE_SSE
  result.sse_columns[0] = _mm_add_ps(left.sse_columns[0], right.sse_columns[0]);
  result.sse_columns[1] = _mm_add_ps(left.sse_columns[1], right.sse_columns[1]);
  result.sse_columns[2] = _mm_add_ps(left.sse_columns[2], right.sse_columns[2]);
  result.sse_columns[3] = _mm_add_ps(left.sse_columns[3], right.sse_columns[3]);
#else
  for (unsigned char i = 0; i < 16; i++) {
    result.elems[i] = left.elems[i] + right.elems[i];
  }
#endif
  return result;
}

// @TESTED
GMATH_INLINE mat4_t mat4_sub(mat4_t left, mat4_t right) {
  mat4_t result;
#ifdef GMATH_USE_SSE
  result.sse_columns[0] = _mm_sub_ps(left.sse_columns[0], right.sse_columns[0]);
  result.sse_columns[1] = _mm_sub_ps(left.sse_columns[1], right.sse_columns[1]);
  result.sse_columns[2] = _mm_sub_ps(left.sse_columns[2], right.sse_columns[2]);
  result.sse_columns[3] = _mm_sub_ps(left.sse_columns[3], right.sse_columns[3]);
#else
  for (unsigned char i = 0; i < 16; i++) {
    result.elems[i] = left.elems[i] - right.elems[i];
  }
#endif
  return result;
}

// @TESTED
GMATH_INLINE mat4_t mat4_muls(mat4_t left, float right) {
  mat4_t result;
#ifdef GMATH_USE_SSE
  __m128 sse_scalar = _mm_load_ps1(&right);
  result.sse_columns[0] = _mm_mul_ps(left.sse_columns[0], sse_scalar);
  result.sse_columns[1] = _mm_mul_ps(left.sse_columns[1], sse_scalar);
  result.sse_columns[2] = _mm_mul_ps(left.sse_columns[2], sse_scalar);
  result.sse_columns[3] = _mm_mul_ps(left.sse_columns[3], sse_scalar);
#else
  for (unsigned char i = 0; i < 16; i++) {
    result.elems[i] = left.elems[i] * right;
  }
#endif
  return result;
}

// @TESTED
GMATH_INLINE mat4_t mat4_divs(mat4_t left, float right) {
  mat4_t result;
#ifdef GMATH_USE_SSE
  __m128 sse_scalar = _mm_load_ps1(&right);
  result.sse_columns[0] = _mm_div_ps(left.sse_columns[0], sse_scalar);
  result.sse_columns[1] = _mm_div_ps(left.sse_columns[1], sse_scalar);
  result.sse_columns[2] = _mm_div_ps(left.sse_columns[2], sse_scalar);
  result.sse_columns[3] = _mm_div_ps(left.sse_columns[3], sse_scalar);
#else
  for (unsigned char i = 0; i < 16; i++) {
    result.elems[i] = left.elems[i] / right;
  }
#endif
  return result;
}

// @TESTED
GMATH_INLINE mat4_t mat4_mul(mat4_t left, mat4_t right) {
  mat4_t result;
#ifdef GMATH_USE_SSE
  for (int i = 0; i < 4; i++) {
    __m128 brod1 = _mm_set1_ps(left.elems[4 * i + 0]);
    __m128 brod2 = _mm_set1_ps(left.elems[4 * i + 1]);
    __m128 brod3 = _mm_set1_ps(left.elems[4 * i + 2]);
    __m128 brod4 = _mm_set1_ps(left.elems[4 * i + 3]);
    __m128 row = _mm_add_ps(
        _mm_add_ps(
            _mm_mul_ps(brod1, right.sse_columns[0]),
            _mm_mul_ps(brod2, right.sse_columns[1])),
        _mm_add_ps(
            _mm_mul_ps(brod3, right.sse_columns[2]),
            _mm_mul_ps(brod4, right.sse_columns[3])));
    _mm_store_ps(&result.elems[4 * i], row);
  }
#else
  *result.= {{{0}}};
  for (unsigned char i = 0; i < 4; i++) {
    for (unsigned char j = 0; j < 4; j++) {
      for (unsigned char p = 0; p < 4; p++) {
        result.columns[i][j] += left.columns[i][p] * right.columns[p][j];
      }
    }
  }
#endif
  return result;
}

// @TESTED: compatible with glm
GMATH_INLINE mat4_t
mat4_perspective(float fovy, float aspect_ratio, float znear, float zfar) {
  mat4_t result = mat4_zero();

  float tan_half_fovy = tan(fovy / 2.0f);

  result.columns[0][0] = 1.0f / (aspect_ratio * tan_half_fovy);
  result.columns[1][1] = 1.0f / tan_half_fovy;
  result.columns[2][2] = -(zfar + znear) / (zfar - znear);
  result.columns[2][3] = -1.0f;
  result.columns[3][2] = -(2.0 * zfar * znear) / (zfar - znear);

  return result;
}

// @TESTED: compatible with glm
GMATH_INLINE mat4_t mat4_look_at(vec3_t eye, vec3_t center, vec3_t up) {
  vec3_t f = vec3_normalize(vec3_sub(center, eye));
  vec3_t s = vec3_normalize(vec3_cross(f, up));
  vec3_t u = vec3_cross(s, f);

  mat4_t result = mat4_identity();

  result.columns[0][0] = s.x;
  result.columns[1][0] = s.y;
  result.columns[2][0] = s.z;

  result.columns[0][1] = u.x;
  result.columns[1][1] = u.y;
  result.columns[2][1] = u.z;

  result.columns[0][2] = -f.x;
  result.columns[1][2] = -f.y;
  result.columns[2][2] = -f.z;

  result.columns[3][0] = -vec3_dot(s, eye);
  result.columns[3][1] = -vec3_dot(u, eye);
  result.columns[3][2] = vec3_dot(f, eye);

  return result;
}

// @TESTED: compatible with glm
GMATH_INLINE quat_t mat4_to_quat(mat4_t mat) {
  quat_t result;
  float trace = mat.columns[0][0] + mat.columns[1][1] + mat.columns[2][2];
  if (trace > 0.0f) {
    float s = sqrt(1.0f + trace) * 2.0f;
    result.w = 0.25f * s;
    result.x = (mat.columns[1][2] - mat.columns[2][1]) / s;
    result.y = (mat.columns[2][0] - mat.columns[0][2]) / s;
    result.z = (mat.columns[0][1] - mat.columns[1][0]) / s;
  } else if (
      mat.columns[0][0] > mat.columns[1][1] &&
      mat.columns[0][0] > mat.columns[2][2]) {
    float s =
        sqrt(1.0f + mat.columns[0][0] - mat.columns[1][1] - mat.columns[2][2]) *
        2.0f;
    result.w = (mat.columns[1][2] - mat.columns[2][1]) / s;
    result.x = 0.25f * s;
    result.y = (mat.columns[1][0] + mat.columns[0][1]) / s;
    result.z = (mat.columns[2][0] + mat.columns[0][2]) / s;
  } else if (mat.columns[1][1] > mat.columns[2][2]) {
    float s =
        sqrt(1.0f + mat.columns[1][1] - mat.columns[0][0] - mat.columns[2][2]) *
        2.0f;
    result.w = (mat.columns[2][0] - mat.columns[0][2]) / s;
    result.x = (mat.columns[1][0] + mat.columns[0][1]) / s;
    result.y = 0.25f * s;
    result.z = (mat.columns[2][1] + mat.columns[1][2]) / s;
  } else {
    float s =
        sqrt(1.0f + mat.columns[2][2] - mat.columns[0][0] - mat.columns[1][1]) *
        2.0f;
    result.w = (mat.columns[0][1] - mat.columns[1][0]) / s;
    result.x = (mat.columns[2][0] + mat.columns[0][2]) / s;
    result.y = (mat.columns[2][1] + mat.columns[1][2]) / s;
    result.z = 0.25f * s;
  }
  return result;
}

// @TESTED: compatible with glm
GMATH_INLINE mat4_t mat4_translate(mat4_t mat, vec3_t translation) {
  mat4_t result = mat;
  result.columns[3][0] += translation.x;
  result.columns[3][1] += translation.y;
  result.columns[3][2] += translation.z;
  return result;
}

// @TESTED: compatible with glm
GMATH_INLINE mat4_t mat4_scale(mat4_t mat, vec3_t scale) {
  mat4_t result = mat;
  result.columns[0][0] *= scale.x;
  result.columns[1][1] *= scale.y;
  result.columns[2][2] *= scale.z;
  return result;
}

// @TESTED: compatible with glm
GMATH_INLINE mat4_t mat4_rotate(mat4_t mat, float angle, vec3_t axis) {
  float c = cos(angle);
  float s = sin(angle);

  axis = vec3_normalize(axis);
  vec3_t temp = vec3_muls(axis, (1.0f - c));

  mat4_t rotate;
  rotate.columns[0][0] = c + temp.x * axis.x;
  rotate.columns[0][1] = temp.x * axis.y + s * axis.z;
  rotate.columns[0][2] = temp.x * axis.z - s * axis.y;

  rotate.columns[1][0] = temp.y * axis.x - s * axis.z;
  rotate.columns[1][1] = c + temp.y * axis.y;
  rotate.columns[1][2] = temp.y * axis.z + s * axis.x;

  rotate.columns[2][0] = temp.z * axis.x + s * axis.y;
  rotate.columns[2][1] = temp.z * axis.y - s * axis.x;
  rotate.columns[2][2] = c + temp.z * axis.z;

  mat4_t result;
  result.vectors[0] = vec4_add(
      vec4_add(
          vec4_muls(mat.vectors[0], rotate.columns[0][0]),
          vec4_muls(mat.vectors[1], rotate.columns[0][1])),
      vec4_muls(mat.vectors[2], rotate.columns[0][2]));
  result.vectors[1] = vec4_add(
      vec4_add(
          vec4_muls(mat.vectors[0], rotate.columns[1][0]),
          vec4_muls(mat.vectors[1], rotate.columns[1][1])),
      vec4_muls(mat.vectors[2], rotate.columns[1][2]));
  result.vectors[2] = vec4_add(
      vec4_add(
          vec4_muls(mat.vectors[0], rotate.columns[2][0]),
          vec4_muls(mat.vectors[1], rotate.columns[2][1])),
      vec4_muls(mat.vectors[2], rotate.columns[2][2]));
  result.vectors[3] = mat.vectors[3];
  return result;
}

#ifdef __cplusplus
}
#endif

#endif
