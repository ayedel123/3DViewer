#include "../backTests.h"

START_TEST(case_1) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[16] = {0.0f};
  A[0] = 1.0f;
  A[5] = 1.0f;
  A[10] = 1.0f;
  A[15] = 1.0f;
  translatef(0, 0, 5, A);
  // printMatrix(A);
  float tru[16] = {0.0f};
  tru[0] = 1.0f;
  tru[5] = 1.0f;
  tru[10] = 1.0f;
  tru[15] = 1.0f;
  tru[11] = 5.0f;
  ASSERT_MATRIX_EQ(tru, A);
}
END_TEST

START_TEST(case_2) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[16] = {0.0f};
  A[0] = 1.0f;
  A[5] = 1.0f;
  A[10] = 1.0f;
  A[15] = 1.0f;
  translatef(0, 5, 0, A);
  float tru[16] = {0.0f};
  tru[0] = 1.0f;
  tru[5] = 1.0f;
  tru[10] = 1.0f;
  tru[15] = 1.0f;
  tru[7] = 5.0f;
  ASSERT_MATRIX_EQ(tru, A);
}
END_TEST

START_TEST(case_3) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[16] = {0.0f};
  A[0] = 1.0f;
  A[5] = 1.0f;
  A[10] = 1.0f;
  A[15] = 1.0f;
  translatef(5, 0, 0, A);
  float tru[16] = {0.0f};
  tru[0] = 1.0f;
  tru[5] = 1.0f;
  tru[10] = 1.0f;
  tru[15] = 1.0f;
  tru[3] = 5.0f;
  ASSERT_MATRIX_EQ(tru, A);
}
END_TEST
START_TEST(case_4) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[16] = {0.0f};
  A[0] = 1.0f;
  A[5] = 1.0f;
  A[10] = 1.0f;
  A[15] = 1.0f;
  translatef(2, 3, 1, A);
  float tru[16] = {0};
  tru[0] = 1.0f;
  tru[5] = 1.0f;
  tru[10] = 1.0f;
  tru[15] = 1.0f;
  tru[3] = 2.0f;
  tru[7] = 3.0f;
  tru[11] = 1.0f;
  ASSERT_MATRIX_EQ(tru, A);
}
END_TEST

START_TEST(case_5) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[16] = {0};
  A[0] = 1.0f;
  A[5] = 1.0f;
  A[10] = 1.0f;
  A[15] = 1.0f;
  translatef(1, -2, 0, A);
  float tru[16] = {0};
  tru[0] = 1.0f;
  tru[5] = 1.0f;
  tru[10] = 1.0f;
  tru[15] = 1.0f;
  tru[3] = 1.0f;
  tru[7] = -2.0f;
  tru[11] = 0.0f;
  ASSERT_MATRIX_EQ(tru, A);
}
END_TEST

START_TEST(case_6) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[16] = {0.0f};
  A[0] = 1.0f;
  A[5] = 1.0f;
  A[10] = 1.0f;
  A[15] = 1.0f;
  translatef(-3, 0, 2, A);
  float tru[16] = {0.0f};
  tru[0] = 1.0f;
  tru[5] = 1.0f;
  tru[10] = 1.0f;
  tru[15] = 1.0f;
  tru[3] = -3.0f;
  tru[7] = 0.0f;
  tru[11] = 2.0f;
  ASSERT_MATRIX_EQ(tru, A);
}
END_TEST

Suite *translatefTestSuite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("Translatef");
  tc = tcase_create("test");

  tcase_add_test(tc, case_1);
  tcase_add_test(tc, case_2);
  tcase_add_test(tc, case_3);
  tcase_add_test(tc, case_4);
  tcase_add_test(tc, case_5);
  tcase_add_test(tc, case_6);

  suite_add_tcase(s, tc);
  return s;
}