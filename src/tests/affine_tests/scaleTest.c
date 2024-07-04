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
  scale(5.0f, 5.0f, 5.0f, A);
  float tru[16] = {0.0f};
  tru[0] = 5.0f;
  tru[5] = 5.0f;
  tru[10] = 5.0f;
  tru[15] = 1.0f;
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
  scale(0.5f, 5.0f, 1.2f, A);
  float tru[16] = {0.0f};
  tru[0] = 0.5f;
  tru[5] = 5.0f;
  tru[10] = 1.2f;
  tru[15] = 1.0f;
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
  scale(1.0f, 1.0f, 1.0f, A);
  float tru[16] = {0.0f};
  tru[0] = 1.0f;
  tru[5] = 1.0f;
  tru[10] = 1.0f;
  tru[15] = 1.0f;
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
  scale(0.0f, 0.0f, 0.0f, A);
  float tru[16] = {0.0f};
  tru[15] = 1.0f;
  ASSERT_MATRIX_EQ(tru, A);
}
END_TEST

Suite *scaleTestSuite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("Scale");
  tc = tcase_create("test");

  tcase_add_test(tc, case_1);
  tcase_add_test(tc, case_2);
  tcase_add_test(tc, case_3);
  tcase_add_test(tc, case_4);

  suite_add_tcase(s, tc);
  return s;
}