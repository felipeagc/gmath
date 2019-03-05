#ifndef GMATH_QUAT_H
#define GMATH_QUAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "mat4.h"
#include "types.h"
#include <assert.h>
#include <math.h>

// @TESTED: compatible with glm
GMATH_INLINE float quat_dot(quat_t left, quat_t right) {
  return (left.x * right.x) + (left.y * right.y) + (left.z * right.z) +
         (left.w * right.w);
}

// @TESTED: compatible with glm
GMATH_INLINE quat_t quat_normalize(quat_t left) {
  float length = sqrtf(quat_dot(left, left));
  if (length <= 0.0f) {
    return (quat_t){0.0f, 0.0f, 0.0f, 1.0f};
  }
  float one_over_length = 1.0f / length;
  return (quat_t){left.x * one_over_length,
                  left.y * one_over_length,
                  left.z * one_over_length,
                  left.w * one_over_length};
}

// @TESTED: compatible with glm
GMATH_INLINE quat_t quat_from_axis_angle(vec3_t axis, float angle) {
  float s = sin(angle / 2.0f);
  quat_t result;
  result.x = axis.x * s;
  result.y = axis.y * s;
  result.z = axis.z * s;
  result.w = cos(angle / 2.0f);
  return result;
}

// @TESTED: compatible with glm
GMATH_INLINE void quat_to_axis_angle(quat_t quat, vec3_t *axis, float *angle) {
  quat = quat_normalize(quat);
  *angle = 2.0f * acos(quat.w);
  float s = sqrt(1.0f - quat.w * quat.w);
  if (s < 0.001) {
    axis->x = quat.x;
    axis->y = quat.y;
    axis->z = quat.z;
  } else {
    axis->x = quat.x / s;
    axis->y = quat.y / s;
    axis->z = quat.z / s;
  }
}

// @TESTED: compatible with glm
GMATH_INLINE quat_t quat_conjugate(quat_t quat) {
  quat_t result;
  result.w = quat.w;
  result.x = -quat.x;
  result.y = -quat.y;
  result.z = -quat.z;
  return result;
}

// @TESTED: compatible with glm
GMATH_INLINE mat4_t quat_to_mat4(quat_t quat) {
  mat4_t result = mat4_identity();

  float xx = quat.x * quat.x;
  float yy = quat.y * quat.y;
  float zz = quat.z * quat.z;
  float xy = quat.x * quat.y;
  float xz = quat.x * quat.z;
  float yz = quat.y * quat.z;
  float wx = quat.w * quat.x;
  float wy = quat.w * quat.y;
  float wz = quat.w * quat.z;

  result.columns[0][0] = 1.0f - 2.0f * (yy + zz);
  result.columns[0][1] = 2.0f * (xy + wz);
  result.columns[0][2] = 2.0f * (xz - wy);

  result.columns[1][0] = 2.0f * (xy - wz);
  result.columns[1][1] = 1.0f - 2.0f * (xx + zz);
  result.columns[1][2] = 2.0f * (yz + wx);

  result.columns[2][0] = 2.0f * (xz + wy);
  result.columns[2][1] = 2.0f * (yz - wx);
  result.columns[2][2] = 1.0f - 2.0f * (xx + yy);

  return result;
}

// @TESTED: compatible with glm
GMATH_INLINE quat_t quat_look_at(vec3_t direction, vec3_t up) {
  float m[3][3] = {
      {0, 0, 0},
      {0, 0, 0},
      {0, 0, 0},
  };

  vec3_t col2 = vec3_muls(direction, -1.0f);
  m[2][0] = col2.x;
  m[2][1] = col2.y;
  m[2][2] = col2.z;

  vec3_t col0 = vec3_normalize(vec3_cross(up, col2));
  m[0][0] = col0.x;
  m[0][1] = col0.y;
  m[0][2] = col0.z;

  vec3_t col1 = vec3_cross(col2, col0);
  m[1][0] = col1.x;
  m[1][1] = col1.y;
  m[1][2] = col1.z;

  float x = m[0][0] - m[1][1] - m[2][2];
  float y = m[1][1] - m[0][0] - m[2][2];
  float z = m[2][2] - m[0][0] - m[1][1];
  float w = m[0][0] + m[1][1] + m[2][2];

  int biggest_index = 0;
  float biggest = w;
  if (x > biggest) {
    biggest = x;
    biggest_index = 1;
  }
  if (y > biggest) {
    biggest = y;
    biggest_index = 2;
  }
  if (z > biggest) {
    biggest = z;
    biggest_index = 3;
  }

  float biggest_val = sqrt(biggest + 1.0f) * 0.5f;
  float mult = 0.25f / biggest_val;

  switch (biggest_index) {
  case 0:
    return (quat_t){
        (m[1][2] - m[2][1]) * mult,
        (m[2][0] - m[0][2]) * mult,
        (m[0][1] - m[1][0]) * mult,
        biggest_val,
    };
  case 1:
    return (quat_t){
        biggest_val,
        (m[0][1] + m[1][0]) * mult,
        (m[2][0] + m[0][2]) * mult,
        (m[1][2] - m[2][1]) * mult,
    };
  case 2:
    return (quat_t){
        (m[0][1] + m[1][0]) * mult,
        biggest_val,
        (m[1][2] + m[2][1]) * mult,
        (m[2][0] - m[0][2]) * mult,
    };
  case 3:
    return (quat_t){
        (m[2][0] + m[0][2]) * mult,
        (m[1][2] + m[2][1]) * mult,
        biggest_val,
        (m[0][1] - m[1][0]) * mult,
    };
  default:
    assert(0 != 0);
  }
}

#ifdef __cplusplus
}
#endif

#endif
