#include <gmath.h>
#include <unity.h>

void test_mat4_size() { TEST_ASSERT(sizeof(mat4_t) == sizeof(float) * 16); }

void test_mat4_zero() {
  mat4_t mat = mat4_zero();

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(mat.cols[i][j], 0.0f);
    }
  }
}

void test_mat4_diagonal() {
  mat4_t mat = mat4_diagonal(2.0f);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j) {
        TEST_ASSERT_EQUAL_FLOAT(mat.cols[i][j], 2.0f);
      } else {
        TEST_ASSERT_EQUAL_FLOAT(mat.cols[i][j], 0.0f);
      }
    }
  }
}

void test_mat4_identity() {
  mat4_t mat = mat4_identity();

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j) {
        TEST_ASSERT_EQUAL_FLOAT(mat.cols[i][j], 1.0f);
      } else {
        TEST_ASSERT_EQUAL_FLOAT(mat.cols[i][j], 0.0f);
      }
    }
  }
}

void test_mat4_transpose_identity() {
  mat4_t mata = mat4_identity();
  mat4_t matb = mat4_transpose(mata);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(mata.cols[i][j], matb.cols[i][j]);
    }
  }
}

void test_mat4_transpose() {
  mat4_t mata = mat4_identity();
  mata.cols[0][1] = 5.0f;
  mata.cols[0][2] = 6.0f;
  mata.cols[0][3] = 7.0f;
  mata.cols[1][3] = 8.0f;
  mata.cols[2][3] = 9.0f;
  mata.cols[3][2] = 10.0f;
  mat4_t matb = mat4_transpose(mata);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(mata.cols[i][j], matb.cols[j][i]);
    }
  }
}

void test_mat4_addition() {
  mat4_t mata = mat4_identity();
  mata.cols[0][1] = 5.0f;
  mat4_t matb = mat4_identity();
  matb.cols[0][1] = 1.0f;
  matb.cols[0][3] = 5.0f;
  matb.cols[1][2] = 3.0f;

  mat4_t sum = mat4_add(mata, matb);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(
          mata.cols[i][j] + matb.cols[i][j], sum.cols[i][j]);
    }
  }
}

void test_mat4_subtraction() {
  mat4_t mata = mat4_identity();
  mata.cols[0][1] = 5.0f;
  mat4_t matb = mat4_identity();
  matb.cols[0][1] = 1.0f;
  matb.cols[0][3] = 5.0f;
  matb.cols[1][2] = 3.0f;

  mat4_t sub = mat4_sub(mata, matb);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(
          mata.cols[i][j] - matb.cols[i][j], sub.cols[i][j]);
    }
  }
}

void test_mat4_multiplication_scalar() {
  mat4_t mat = mat4_identity();
  mat4_t mul = mat4_muls(mat, 5.0f);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(mat.cols[i][j] * 5.0f, mul.cols[i][j]);
    }
  }
}

void test_mat4_division_scalar() {
  mat4_t mat = mat4_identity();
  mat4_t div = mat4_divs(mat, 5.0f);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(mat.cols[i][j] / 5.0f, div.cols[i][j]);
    }
  }
}

void test_mat4_multiplication() {
  mat4_t mata = {{
      {1, 2, 1, 1},
      {0, 1, 0, 1},
      {1, 1, 1, 1},
      {1, 1, 1, 1},
  }};

  mat4_t matb = {{
      {2, 5, 1, 1},
      {6, 7, 1, 1},
      {1, 8, 1, 1},
      {1, 1, 1, 1},
  }};

  mat4_t mul = mat4_mul(mata, matb);

  mat4_t expected = {{
      {16, 28, 5, 5},
      {7, 8, 2, 2},
      {10, 21, 4, 4},
      {10, 21, 4, 4},
  }};

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      TEST_ASSERT_EQUAL_FLOAT(mul.cols[i][j], expected.cols[i][j]);
    }
  }
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_mat4_size);
  RUN_TEST(test_mat4_zero);
  RUN_TEST(test_mat4_diagonal);
  RUN_TEST(test_mat4_identity);
  RUN_TEST(test_mat4_transpose_identity);
  RUN_TEST(test_mat4_transpose);
  RUN_TEST(test_mat4_addition);
  RUN_TEST(test_mat4_subtraction);
  RUN_TEST(test_mat4_multiplication_scalar);
  RUN_TEST(test_mat4_division_scalar);
  RUN_TEST(test_mat4_multiplication);

  return UNITY_END();
}
