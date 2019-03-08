#include <unity.h>
#include <gmath.h>

void test_vec3_addition() {
  vec3_t v1 = {1, 2, 3};
  vec3_t v2 = {4, 5, 6};
  vec3_t sum = vec3_add(v1, v2);

  TEST_ASSERT_EQUAL_FLOAT(sum.x, 1 + 4);
  TEST_ASSERT_EQUAL_FLOAT(sum.y, 2 + 5);
  TEST_ASSERT_EQUAL_FLOAT(sum.z, 3 + 6);
}

void test_vec3_multiplication() {
  vec3_t v1 = {1, 2, 3};
  vec3_t v2 = {4, 5, 6};
  vec3_t mul = vec3_mul(v1, v2);

  TEST_ASSERT_EQUAL_FLOAT(mul.x, 1 * 4);
  TEST_ASSERT_EQUAL_FLOAT(mul.y, 2 * 5);
  TEST_ASSERT_EQUAL_FLOAT(mul.z, 3 * 6);
}

void test_vec3_dot_product() {
  vec3_t v1 = {1, 2, 3};
  vec3_t v2 = {4, 5, 6};
  float dot = vec3_dot(v1, v2);

  TEST_ASSERT_EQUAL_FLOAT(dot, 1 * 4 + 2 * 5 + 3 * 6);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_vec3_addition);
  RUN_TEST(test_vec3_multiplication);
  RUN_TEST(test_vec3_dot_product);

  return UNITY_END();
}
