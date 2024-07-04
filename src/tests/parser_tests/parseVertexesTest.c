#include "../backTests.h"

START_TEST(no_vals) {
  Model model;
  initModel(&model);
  fillModel(&model, 1, 0);
  char *line = "v   ";
  int status = parseVertexes(&model, 0, line);
  freeModel(&model);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
}
END_TEST

START_TEST(one_val_1) {
  Model model;
  initModel(&model);
  fillModel(&model, 1, 0);
  char *line = "v 1  ";
  int status = parseVertexes(&model, 0, line);
  freeModel(&model);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
}
END_TEST

START_TEST(two_vals) {
  Model model;
  initModel(&model);
  fillModel(&model, 1, 0);
  char *line = "v 1 2 ";
  int status = parseVertexes(&model, 0, line);
  freeModel(&model);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
}
END_TEST

START_TEST(one_val_2) {
  Model model;
  initModel(&model);
  fillModel(&model, 1, 0);
  char *line = "v  123  ";
  int status = parseVertexes(&model, 0, line);
  freeModel(&model);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
}
END_TEST

START_TEST(incorrect_val_1) {
  Model model;
  initModel(&model);
  fillModel(&model, 1, 0);
  char *line = "v 1.1.1  ";
  int status = parseVertexes(&model, 0, line);
  freeModel(&model);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
}
END_TEST

START_TEST(incorrect_val_2) {
  Model model;
  initModel(&model);
  fillModel(&model, 1, 0);
  char *line = "v  . 123 ";
  int status = parseVertexes(&model, 0, line);
  freeModel(&model);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
}
END_TEST

START_TEST(incorrect_val_3) {
  Model model;
  initModel(&model);
  fillModel(&model, 1, 0);
  char *line = "v /123123";
  int status = parseVertexes(&model, 0, line);
  freeModel(&model);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
}
END_TEST

START_TEST(correct_val_1) {
  Model model;
  initModel(&model);
  fillModel(&model, 1, 0);
  char *line = "V 1 2 3 ";
  int status = parseVertexes(&model, 0, line);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_double_eq(1.0, model.vertexes[0]);
  ck_assert_double_eq(2.0, model.vertexes[1]);
  ck_assert_double_eq(3.0, model.vertexes[2]);
  freeModel(&model);
}
END_TEST

START_TEST(correct_val_2) {
  Model model;
  initModel(&model);
  fillModel(&model, 1, 0);
  char *line = "V     1.23 2.12313 3.123213 ";
  int status = parseVertexes(&model, 0, line);

  ck_assert_int_eq(status, SUCCESS);
  ck_assert_double_eq(1.23, model.vertexes[0]);
  ck_assert_double_eq(2.12313, model.vertexes[1]);
  ck_assert_double_eq(3.123213, model.vertexes[2]);
  freeModel(&model);
}
END_TEST

START_TEST(correct_val_3) {
  Model model;
  initModel(&model);
  fillModel(&model, 1, 0);
  char *line = "V 1.23    2.12313  -1231233.123213 ";
  int status = parseVertexes(&model, 0, line);

  ck_assert_int_eq(status, SUCCESS);
  ck_assert_double_eq(1.23, model.vertexes[0]);
  ck_assert_double_eq(2.12313, model.vertexes[1]);
  ck_assert_double_eq(-1231233.123213, model.vertexes[2]);
  freeModel(&model);
}
END_TEST

START_TEST(correct_val_4) {
  Model model;
  initModel(&model);
  fillModel(&model, 1, 0);
  char *line = "V 1.23    2.12313  -1231233.123213 122131312";
  int status = parseVertexes(&model, 0, line);

  ck_assert_int_eq(status, SUCCESS);
  ck_assert_double_eq(1.23, model.vertexes[0]);
  ck_assert_double_eq(2.12313, model.vertexes[1]);
  ck_assert_double_eq(-1231233.123213, model.vertexes[2]);
  freeModel(&model);
}
END_TEST

START_TEST(correct_val_5) {
  Model model;
  initModel(&model);
  fillModel(&model, 1, 0);
  char *line = "V 1.23    2.12313  -1231233.123213 asdassdsad";
  int status = parseVertexes(&model, 0, line);

  ck_assert_int_eq(status, SUCCESS);
  ck_assert_double_eq(1.23, model.vertexes[0]);
  ck_assert_double_eq(2.12313, model.vertexes[1]);
  ck_assert_double_eq(-1231233.123213, model.vertexes[2]);
  freeModel(&model);
}
END_TEST

Suite *parseVertexesSuite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("Parse Vertexes test");
  tc = tcase_create("test");

  tcase_add_test(tc, no_vals);
  tcase_add_test(tc, one_val_1);
  tcase_add_test(tc, one_val_2);
  tcase_add_test(tc, incorrect_val_1);
  tcase_add_test(tc, incorrect_val_2);
  tcase_add_test(tc, incorrect_val_3);
  tcase_add_test(tc, correct_val_1);
  tcase_add_test(tc, correct_val_2);
  tcase_add_test(tc, correct_val_3);
  tcase_add_test(tc, correct_val_4);
  tcase_add_test(tc, correct_val_5);
  tcase_add_test(tc, no_vals);
  tcase_add_test(tc, two_vals);
  suite_add_tcase(s, tc);
  return s;
}
