#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <gmath.h>
#include <unity.h>

void test_glm_mat4_perspective() {
  mat4_t mat = mat4_perspective(70.0f, 16.0f / 9.0f, 0.01f, 300.0f);
  glm::mat4 glm_mat = glm::perspective(70.0f, 16.0f / 9.0f, 0.01f, 300.0f);

  TEST_ASSERT(GLM_CONFIG_CLIP_CONTROL == GLM_CLIP_CONTROL_RH_NO);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(mat.columns[i][j], glm_mat[i][j]);
    }
  }
}

void test_glm_mat4_look_at() {
  mat4_t mat = mat4_look_at({1.0, -1.0, 0.0}, {3.0, 3.0, 3.0}, {0.0, 1.0, 0.0});
  glm::mat4 glm_mat =
      glm::lookAt(glm::vec3{1.0, -1.0, 0.0}, {3.0, 3.0, 3.0}, {0.0, 1.0, 0.0});

  TEST_ASSERT(GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_RH_BIT);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(mat.columns[i][j], glm_mat[i][j]);
    }
  }
}

void test_glm_mat4_to_quat() {
  mat4_t mat = mat4_rotate(mat4_identity(), 30.0f, {0.5, 0.3, 0.1});
  glm::mat4 glm_mat = glm::rotate(glm::mat4(1.0f), 30.0f, {0.5, 0.3, 0.1});

  quat_t quat = mat4_to_quat(mat);
  glm::quat glm_quat = glm::quat_cast(glm_mat);

  TEST_ASSERT_EQUAL_FLOAT(quat.x, glm_quat.x);
  TEST_ASSERT_EQUAL_FLOAT(quat.y, glm_quat.y);
  TEST_ASSERT_EQUAL_FLOAT(quat.z, glm_quat.z);
  TEST_ASSERT_EQUAL_FLOAT(quat.w, glm_quat.w);
}

void test_glm_mat4_translate() {
  mat4_t mat = mat4_translate(mat4_identity(), {1.0, 2.0, 3.0});
  glm::mat4 glm_mat = glm::translate(glm::mat4(1.0f), {1.0, 2.0, 3.0});

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(mat.columns[i][j], glm_mat[i][j]);
    }
  }
}

void test_glm_mat4_scale() {
  mat4_t mat = mat4_scale(mat4_identity(), {1.0, 2.0, 3.0});
  glm::mat4 glm_mat = glm::scale(glm::mat4(1.0f), {1.0, 2.0, 3.0});

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(mat.columns[i][j], glm_mat[i][j]);
    }
  }
}

void test_glm_mat4_rotate() {
  mat4_t mat = mat4_rotate(mat4_identity(), 30.0f, {0.5, 0.3, 0.1});
  glm::mat4 glm_mat = glm::rotate(glm::mat4(1.0f), 30.0f, {0.5, 0.3, 0.1});

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(mat.columns[i][j], glm_mat[i][j]);
    }
  }
}

void test_glm_quat_dot() {
  float dot = quat_dot({1, 2, 3, 4}, {5, 6, 7, 8});
  float glm_dot = glm::dot(glm::quat{1, 2, 3, 4}, glm::quat{5, 6, 7, 8});

  TEST_ASSERT_EQUAL_FLOAT(dot, glm_dot);
}

void test_glm_quat_normalize() {
  quat_t quat = quat_normalize({1, 2, 3, 4}); // x, y, z, w
  glm::quat glm_quat = glm::normalize(glm::quat{4, 1, 2, 3}); // w, x, y, z

  TEST_ASSERT_EQUAL_FLOAT(quat.x, glm_quat.x);
  TEST_ASSERT_EQUAL_FLOAT(quat.y, glm_quat.y);
  TEST_ASSERT_EQUAL_FLOAT(quat.z, glm_quat.z);
  TEST_ASSERT_EQUAL_FLOAT(quat.w, glm_quat.w);
}

void test_glm_quat_from_axis_angle() {
  quat_t quat = quat_from_axis_angle(vec3_normalize({1, 2, 3}), 30.0f) ;
  glm::quat glm_quat = glm::angleAxis(30.0f, glm::normalize(glm::vec3{1, 2, 3}));

  TEST_ASSERT_EQUAL_FLOAT(quat.x, glm_quat.x);
  TEST_ASSERT_EQUAL_FLOAT(quat.y, glm_quat.y);
  TEST_ASSERT_EQUAL_FLOAT(quat.z, glm_quat.z);
  TEST_ASSERT_EQUAL_FLOAT(quat.w, glm_quat.w);
}

void test_glm_quat_to_axis_angle() {
  quat_t quat = quat_from_axis_angle(vec3_normalize({1, 2, 3}), 30.0f) ;
  vec3_t axis;
  float angle;
  quat_to_axis_angle(quat, &axis, &angle);

  glm::quat glm_quat = glm::angleAxis(30.0f, glm::normalize(glm::vec3{1, 2, 3}));
  glm::vec3 glm_axis = glm::axis(glm_quat);
  float glm_angle = glm::angle(glm_quat);

  TEST_ASSERT_EQUAL_FLOAT(axis.x, glm_axis.x);
  TEST_ASSERT_EQUAL_FLOAT(axis.y, glm_axis.y);
  TEST_ASSERT_EQUAL_FLOAT(axis.z, glm_axis.z);
  TEST_ASSERT_EQUAL_FLOAT(angle, glm_angle);
}

void test_glm_quat_conjugate() {
  quat_t quat = quat_conjugate({1, 2, 3, 4}) ;
  glm::quat glm_quat = glm::conjugate(glm::quat{4, 1, 2, 3});

  TEST_ASSERT_EQUAL_FLOAT(quat.x, glm_quat.x);
  TEST_ASSERT_EQUAL_FLOAT(quat.y, glm_quat.y);
  TEST_ASSERT_EQUAL_FLOAT(quat.z, glm_quat.z);
  TEST_ASSERT_EQUAL_FLOAT(quat.w, glm_quat.w);
}

void test_glm_quat_to_mat4() {
  mat4_t mat = quat_to_mat4(quat_normalize({1, 2, 3, 4})) ;
  glm::mat4 glm_mat = glm::mat4_cast(glm::normalize(glm::quat{4, 1, 2, 3}));

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(mat.columns[i][j], glm_mat[i][j]);
    }
  }
}

void test_glm_quat_look_at() {
  TEST_ASSERT(GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_RH_BIT);

  quat_t quat = quat_look_at({1, 2, 3}, {0, 1, 0});
  glm::quat glm_quat = glm::quatLookAt(glm::vec3{1, 2, 3}, {0, 1, 0});

  TEST_ASSERT_EQUAL_FLOAT(quat.x, glm_quat.x);
  TEST_ASSERT_EQUAL_FLOAT(quat.y, glm_quat.y);
  TEST_ASSERT_EQUAL_FLOAT(quat.z, glm_quat.z);
  TEST_ASSERT_EQUAL_FLOAT(quat.w, glm_quat.w);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_glm_mat4_perspective);
  RUN_TEST(test_glm_mat4_look_at);
  RUN_TEST(test_glm_mat4_to_quat);

  RUN_TEST(test_glm_mat4_translate);
  RUN_TEST(test_glm_mat4_scale);
  RUN_TEST(test_glm_mat4_rotate);

  RUN_TEST(test_glm_quat_dot);
  RUN_TEST(test_glm_quat_normalize);
  RUN_TEST(test_glm_quat_from_axis_angle);
  RUN_TEST(test_glm_quat_to_axis_angle);
  RUN_TEST(test_glm_quat_conjugate);
  RUN_TEST(test_glm_quat_to_mat4);
  RUN_TEST(test_glm_quat_look_at);

  return UNITY_END();
}
