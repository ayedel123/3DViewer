#include "../backTests.h"

START_TEST(case_1) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  rotatef(45, 45, 45, A);
  float tru[] = {2.6464467f,  2.3535533f, 1.2071067f, 4.0f,
                 8.6464462f,  4.3535538f, 4.0355339f, 8.0f,
                 14.6464462f, 6.3535538f, 6.8639607f, 12.0f,
                 20.6464462f, 8.3535528f, 9.6923876f, 16.0f};
  ASSERT_MATRIX_EQ(tru, A);
}
END_TEST

START_TEST(case_2) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  rotatef(0, 0, 45, A);
  float tru[] = {2.1213202f,  0.7071068f, 3.0f,  4.0f,
                 7.7781744f,  0.7071066f, 7.0f,  8.0f,
                 13.4350281f, 0.7071071f, 11.0f, 12.0f,
                 19.0918827,  0.7071075,  15.0f, 16.0f};
  ASSERT_MATRIX_EQ(tru, A);
}
END_TEST

START_TEST(case_3) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  rotatef(0, 45, 0, A);
  // printMatrix(A);
  float tru[] = {-1.4142134f, 2.0f,  2.8284271f,  4.0f,  -1.4142137f, 6.0f,
                 8.4852810f,  8.0f,  -1.4142137f, 10.0f, 14.1421356,  12.0f,
                 -1.4142141f, 14.0f, 19.7989883f, 16.0f};
  // tru = {2.6}
  ASSERT_MATRIX_EQ(tru, A);
}
END_TEST

START_TEST(case_4) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  rotatef(360, 360, 360, A);

  ASSERT_MATRIX_EQ(A, A);
}
END_TEST

START_TEST(case_5) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  rotatef(0, 0, 0, A);

  ASSERT_MATRIX_EQ(A, A);
}
END_TEST

START_TEST(case_6) {
  //  0, 1, 2, 3
  //  4, 5, 6, 7
  //  8, 9,10,11
  // 12,13,14,15
  float A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  rotatef(-45, -60, 15, A);
  float tru[] = {3.2574821f,  -1.6048903f, 0.9017414f,  4.0f,
                 9.9213848f,  -3.3904781f, 0.2660666f,  8.0f,
                 16.5852871f, -5.1760650f, -0.3696084f, 12.0f,
                 23.2491894f, -6.9616518f, -1.0052843f, 16.0f};
  ASSERT_MATRIX_EQ(tru, A);
}
END_TEST

Suite *rotatefTestSuite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("Rotatef");
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