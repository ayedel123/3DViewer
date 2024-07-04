#include "../backTests.h"

START_TEST(no_file) {
  int vertexesCount = 0;
  int facesCount = 0;
  int status = analyzeFile("no_such_file", &vertexesCount, &facesCount);
  ck_assert_int_eq(status, ERROR_MISSING_FILE);
}
END_TEST

START_TEST(empty_file) {
  int vertexesCount = 0;
  int facesCount = 0;
  int status =
      analyzeFile("tests/dataset/empty.txt", &vertexesCount, &facesCount);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
  ck_assert_int_eq(vertexesCount, 0);
  ck_assert_int_eq(facesCount, 0);
}
END_TEST

START_TEST(no_vertexes) {
  int vertexesCount = 0;
  int facesCount = 0;
  ck_assert_int_eq(vertexesCount, 0);
  ck_assert_int_eq(vertexesCount, 0);
  int status =
      analyzeFile("tests/dataset/no_vertexes.txt", &vertexesCount, &facesCount);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
  ck_assert_int_eq(vertexesCount, 0);
  ck_assert_int_eq(facesCount, 4);
}
END_TEST

START_TEST(no_faces) {
  int vertexesCount = 0;
  int facesCount = 0;
  ck_assert_int_eq(vertexesCount, 0);
  ck_assert_int_eq(vertexesCount, 0);
  int status =
      analyzeFile("tests/dataset/no_faces.txt", &vertexesCount, &facesCount);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
  ck_assert_int_eq(vertexesCount, 4);
  ck_assert_int_eq(facesCount, 0);
}
END_TEST

START_TEST(ok_file_1) {
  int vertexesCount = 0;
  int facesCount = 0;
  ck_assert_int_eq(vertexesCount, 0);
  ck_assert_int_eq(vertexesCount, 0);
  int status =
      analyzeFile("tests/dataset/pyramid.txt", &vertexesCount, &facesCount);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(vertexesCount, 5);
  ck_assert_int_eq(facesCount, 6);
}
END_TEST

START_TEST(ok_file_2) {
  int vertexesCount = 0;
  int facesCount = 0;
  ck_assert_int_eq(vertexesCount, 0);
  ck_assert_int_eq(vertexesCount, 0);
  int status =
      analyzeFile("tests/dataset/cringe_cube.txt", &vertexesCount, &facesCount);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(vertexesCount, 8);
  ck_assert_int_eq(facesCount, 12);
}
END_TEST

Suite *analyzeFileSuite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("Analyze file");
  tc = tcase_create("test");

  tcase_add_test(tc, no_file);
  tcase_add_test(tc, empty_file);
  tcase_add_test(tc, no_vertexes);
  tcase_add_test(tc, no_faces);
  tcase_add_test(tc, ok_file_1);
  tcase_add_test(tc, ok_file_2);
  suite_add_tcase(s, tc);
  return s;
}
