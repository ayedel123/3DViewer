#include "../backTests.h"

START_TEST(count_case_1) {
  char *line = "   ";
  int count = countVertexes(line);
  ck_assert_int_eq(count, 0);
}
END_TEST

START_TEST(count_case_2) {
  char *line = "   1 2 3";
  int count = countVertexes(line);
  ck_assert_int_eq(count, 3);
}
END_TEST

START_TEST(count_case_3) {
  char *line = "f adsa1 2 3   ";
  int count = countVertexes(line);
  ck_assert_int_eq(count, -1);
}
END_TEST

START_TEST(count_case_4) {
  char *line = "fffff ";
  int count = countVertexes(line);
  ck_assert_int_eq(count, -1);
}
END_TEST

START_TEST(count_case_5) {
  char *line = "123/123 123132/3 44/12";
  int count = countVertexes(line);
  ck_assert_int_eq(count, 3);
}
END_TEST

START_TEST(count_case_6) {
  char *line = "--1.23/123 .1231.32/3 44/12";
  int count = countVertexes(line);
  ck_assert_int_eq(count, -1);
}
END_TEST

START_TEST(count_case_7) {
  char *line = "12--3/123/12312 12--3132/3/3412 44/12/123";
  int count = countVertexes(line);
  ck_assert_int_eq(count, 3);
}
END_TEST

START_TEST(count_case_8) {
  char *line = "123/123/1asda 123/s1a3s2/344/12";
  int count = countVertexes(line);
  ck_assert_int_eq(count, -1);
}
END_TEST

START_TEST(count_case_9) {
  char *line = "123/123 1231/32/344/12";
  int count = countVertexes(line);
  ck_assert_int_eq(count, 2);
}
END_TEST

START_TEST(count_case_10) {
  char *line = "/123/1/2//3// /1/3/////2/3 //";
  int count = countVertexes(line);
  ck_assert_int_eq(count, 0);
}
END_TEST

Suite *countVertexesSuite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("Count Vertexes");
  tc = tcase_create("test");

  tcase_add_test(tc, count_case_1);
  tcase_add_test(tc, count_case_2);
  tcase_add_test(tc, count_case_3);
  tcase_add_test(tc, count_case_4);
  tcase_add_test(tc, count_case_5);
  tcase_add_test(tc, count_case_6);
  tcase_add_test(tc, count_case_7);
  tcase_add_test(tc, count_case_8);
  tcase_add_test(tc, count_case_9);
  tcase_add_test(tc, count_case_10);

  suite_add_tcase(s, tc);
  return s;
}
