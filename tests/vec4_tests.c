#include <gmath.h>
#include <unity.h>

void test_vec4_size() { TEST_ASSERT(sizeof(vec4_t) == sizeof(float) * 4); }

void test_vec4_addition() {
  vec4_t v1 = {1, 2, 3, 4};
  vec4_t v2 = {5, 6, 7, 8};
  vec4_t sum = vec4_add(v1, v2);

  TEST_ASSERT_EQUAL_FLOAT(sum.x, 1 + 5);
  TEST_ASSERT_EQUAL_FLOAT(sum.y, 2 + 6);
  TEST_ASSERT_EQUAL_FLOAT(sum.z, 3 + 7);
  TEST_ASSERT_EQUAL_FLOAT(sum.w, 4 + 8);
}

void test_vec4_multiplication() {
  vec4_t v1 = {1, 2, 3, 4};
  vec4_t v2 = {5, 6, 7, 8};
  vec4_t mul = vec4_mul(v1, v2);

  TEST_ASSERT_EQUAL_FLOAT(mul.x, 1 * 5);
  TEST_ASSERT_EQUAL_FLOAT(mul.y, 2 * 6);
  TEST_ASSERT_EQUAL_FLOAT(mul.z, 3 * 7);
  TEST_ASSERT_EQUAL_FLOAT(mul.w, 4 * 8);
}

void test_vec4_dot_product() {
  vec4_t v1 = {1, 2, 3, 4};
  vec4_t v2 = {5, 6, 7, 8};
  float dot = vec4_dot(v1, v2);

  TEST_ASSERT_EQUAL_FLOAT(dot, 1 * 5 + 2 * 6 + 3 * 7 + 4 * 8);
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_vec4_size);
  RUN_TEST(test_vec4_addition);
  RUN_TEST(test_vec4_multiplication);
  RUN_TEST(test_vec4_dot_product);

  return UNITY_END();
}
