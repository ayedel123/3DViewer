#include "../backTests.h"

START_TEST(mult_matrix_test_1) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[16] = {0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1};
  float B[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  float C[16] = {0};
  float tru[16] = {18, 20, 22, 24, 18, 20, 22, 24,
                   10, 12, 14, 16, 18, 20, 22, 24};
  s21_mult_matrix(A, B, C);
  ASSERT_MATRIX_EQ(tru, C);
}
END_TEST

START_TEST(mult_matrix_test_2) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[16] = {0};
  A[0] = 1;
  A[5] = 1;
  A[10] = 1;
  A[15] = 1;
  A[3] = 1;
  A[7] = 1;
  A[11] = 1;

  float B[16] = {-1, 2, 3, 4, 5, -6, 7, 8, 9, 10, -11, 12, 13, 14, 15, -16};
  float C[16] = {0};
  float tru[16] = {12, 16, 18, -12, 18, 8,  22, -8,
                   22, 24, 4,  -4,  13, 14, 15, -16};
  s21_mult_matrix(A, B, C);
  ASSERT_MATRIX_EQ(tru, C);
}
END_TEST

START_TEST(mult_matrix_test_3) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[16] = {0};
  A[0] = 1;
  A[5] = 1;
  A[10] = 1;
  A[15] = 1;
  float B[16] = {0, 2, 3, 0, 5, 0, 0, 8, 9, 0, 0, 12, 0, 14, 15, 0};
  float C[16] = {0};
  s21_mult_matrix(A, B, C);
  ASSERT_MATRIX_EQ(B, C);
}
END_TEST

START_TEST(clear_matrix_test) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[16] = {0};
  float B[16] = {12, 16, 18, -12, 18, 8,  22, -8,
                 22, 24, 4,  -4,  13, 14, 15, -16};
  s21_clear_matrix(B);
  ASSERT_MATRIX_EQ(A, B);
}
END_TEST

Suite *matrixTestSuite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("Matrix");
  tc = tcase_create("test");

  tcase_add_test(tc, mult_matrix_test_1);
  tcase_add_test(tc, mult_matrix_test_2);
  tcase_add_test(tc, mult_matrix_test_3);
  tcase_add_test(tc, clear_matrix_test);

  suite_add_tcase(s, tc);
  return s;
}