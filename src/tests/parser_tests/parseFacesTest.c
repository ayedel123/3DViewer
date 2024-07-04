#include "../backTests.h"

START_TEST(case_1) {
  Model model;
  initModel(&model);
  fillModel(&model, 1, 1);
  char *line = "f   ";
  int currentFace = 0;
  int lastVertex = 0;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
  freeModel(&model);
}
END_TEST

START_TEST(case_2) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f  2";
  int currentFace = 0;
  int lastVertex = 0;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(model.faces[0].vertexesCount, 1);
  ck_assert_int_eq(model.faces[0].vertexes[0], 1);

  freeModel(&model);
}
END_TEST

START_TEST(case_3) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f  asdas2";
  int currentFace = 0;
  int lastVertex = 0;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);

  freeModel(&model);
}
END_TEST

START_TEST(case_4) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f  30";
  int currentFace = 0;
  int lastVertex = 0;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);

  freeModel(&model);
}
END_TEST

START_TEST(case_5) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f  -100";
  int currentFace = 0;
  int lastVertex = 0;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);

  freeModel(&model);
}
END_TEST

START_TEST(case_6) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f  -1";
  int currentFace = 0;
  int lastVertex = 0;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
  freeModel(&model);
}
END_TEST

START_TEST(case_7) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f  -1";
  int currentFace = 0;
  int lastVertex = 1;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(model.faces[0].vertexesCount, 1);

  freeModel(&model);
}
END_TEST

START_TEST(case_8) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f  -1 2 3";
  int currentFace = 0;
  int lastVertex = 1;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(model.faces[0].vertexes[0], 0);
  ck_assert_int_eq(model.faces[0].vertexes[1], 1);
  ck_assert_int_eq(model.faces[0].vertexes[2], 2);
  ck_assert_int_eq(model.faces[0].vertexesCount, 3);

  freeModel(&model);
}
END_TEST

START_TEST(case_9) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f  5 2";
  int currentFace = 0;
  int lastVertex = 1;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(model.faces[0].vertexes[0], 4);
  ck_assert_int_eq(model.faces[0].vertexes[1], 1);
  ck_assert_int_eq(model.faces[0].vertexesCount, 2);

  freeModel(&model);
}
END_TEST

START_TEST(case_10) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f  5 2 -1 4 6 -2 8 9";
  int currentFace = 0;
  int lastVertex = 5;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(model.faces[0].vertexes[0], 4);
  ck_assert_int_eq(model.faces[0].vertexes[1], 1);
  ck_assert_int_eq(model.faces[0].vertexes[2], 4);
  ck_assert_int_eq(model.faces[0].vertexes[3], 3);
  ck_assert_int_eq(model.faces[0].vertexes[4], 5);
  ck_assert_int_eq(model.faces[0].vertexes[5], 3);
  ck_assert_int_eq(model.faces[0].vertexes[6], 7);
  ck_assert_int_eq(model.faces[0].vertexes[7], 8);
  ck_assert_int_eq(model.faces[0].vertexesCount, 8);

  freeModel(&model);
}
END_TEST

START_TEST(case_11) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f  /5 /2";
  int currentFace = 0;
  int lastVertex = 1;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
  freeModel(&model);
}
END_TEST

START_TEST(case_12) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f  1/5 2/2";
  int currentFace = 0;
  int lastVertex = 1;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(model.faces[0].vertexes[0], 0);
  ck_assert_int_eq(model.faces[0].vertexes[1], 1);
  ck_assert_int_eq(model.faces[0].vertexesCount, 2);

  freeModel(&model);
}
END_TEST

START_TEST(case_13) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f  1/5/ 2/2/ 8//2";
  int currentFace = 0;
  int lastVertex = 1;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(model.faces[0].vertexes[0], 0);
  ck_assert_int_eq(model.faces[0].vertexes[1], 1);
  ck_assert_int_eq(model.faces[0].vertexes[2], 7);
  ck_assert_int_eq(model.faces[0].vertexesCount, 3);

  freeModel(&model);
}
END_TEST

START_TEST(case_14) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f  1/5 2/2";
  int currentFace = 0;
  int lastVertex = 1;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(model.faces[0].vertexes[0], 0);
  ck_assert_int_eq(model.faces[0].vertexes[1], 1);
  ck_assert_int_eq(model.faces[0].vertexesCount, 2);

  freeModel(&model);
}
END_TEST

START_TEST(case_15) {
  Model model;
  initModel(&model);
  fillModel(&model, 100, 1);
  char *line = "f  10/5 56/2 -40";
  int currentFace = 0;
  int lastVertex = 41;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(model.faces[0].vertexes[0], 9);
  ck_assert_int_eq(model.faces[0].vertexes[1], 55);
  ck_assert_int_eq(model.faces[0].vertexes[2], 1);
  ck_assert_int_eq(model.faces[0].vertexesCount, 3);

  freeModel(&model);
}
END_TEST

START_TEST(case_16) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "   7  \r";
  int currentFace = 0;
  int lastVertex = 2;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(model.faces[0].vertexes[0], 6);
  ck_assert_int_eq(model.faces[0].vertexesCount, 1);

  freeModel(&model);
}
END_TEST

START_TEST(case_17) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f    2//  3//            4// \r";
  int currentFace = 0;
  int lastVertex = 2;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(model.faces[0].vertexes[0], 1);
  ck_assert_int_eq(model.faces[0].vertexes[1], 2);
  ck_assert_int_eq(model.faces[0].vertexes[2], 3);
  ck_assert_int_eq(model.faces[0].vertexesCount, 3);

  freeModel(&model);
}
END_TEST

START_TEST(case_18) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f    2//  3/2.32/    4/asdsa/ \r";
  int currentFace = 0;
  int lastVertex = 2;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);

  freeModel(&model);
}
END_TEST

START_TEST(case_19) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = "f 1 2 --3  \r";
  int currentFace = 0;
  int lastVertex = 4;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);

  freeModel(&model);
}
END_TEST

START_TEST(case_20) {
  Model model;
  initModel(&model);
  fillModel(&model, 10, 1);
  char *line = " // 12\r";
  int currentFace = 0;
  int lastVertex = 4;
  int status = parseFaces(&model, currentFace, lastVertex, line);
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);

  freeModel(&model);
}
END_TEST

Suite *parseFacesSuite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("Parse Faces");
  tc = tcase_create("test");
  tcase_add_test(tc, case_1);
  tcase_add_test(tc, case_2);
  tcase_add_test(tc, case_3);
  tcase_add_test(tc, case_4);
  tcase_add_test(tc, case_5);
  tcase_add_test(tc, case_6);
  tcase_add_test(tc, case_7);
  tcase_add_test(tc, case_8);
  tcase_add_test(tc, case_9);
  tcase_add_test(tc, case_10);
  tcase_add_test(tc, case_11);
  tcase_add_test(tc, case_12);
  tcase_add_test(tc, case_13);
  tcase_add_test(tc, case_14);
  tcase_add_test(tc, case_15);
  tcase_add_test(tc, case_16);
  tcase_add_test(tc, case_17);
  tcase_add_test(tc, case_18);
  tcase_add_test(tc, case_19);
  tcase_add_test(tc, case_20);

  suite_add_tcase(s, tc);
  return s;
}
