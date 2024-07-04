#include "../backTests.h"

START_TEST(case_1) {
  Model model;
  initModel(&model);
  int status = readModel(&model, "no_such_file.txt");
  ck_assert_int_eq(status, ERROR_MISSING_FILE);
  freeModel(&model);
}
END_TEST

START_TEST(case_2) {
  Model model;
  initModel(&model);
  int status = readModel(&model, "tests/dataset/empty.txt");
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
  freeModel(&model);
}
END_TEST

START_TEST(case_3) {
  Model model;
  initModel(&model);
  int status = readModel(&model, "tests/dataset/no_vertexes.txt");
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
  freeModel(&model);
}
END_TEST

START_TEST(case_4) {
  Model model;
  initModel(&model);
  int status = readModel(&model, "tests/dataset/no_faces.txt");
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
  freeModel(&model);
}
END_TEST

START_TEST(case_5) {
  Model model;
  initModel(&model);
  int status = readModel(&model, "tests/dataset/pyramid.txt");
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(model.vertexesCount, 5);
  ck_assert_int_eq(model.facesCount, 6);
  freeModel(&model);
}
END_TEST

START_TEST(case_6) {
  Model model;
  initModel(&model);
  int status = readModel(&model, "tests/dataset/cringe_cube.txt");
  ck_assert_int_eq(status, SUCCESS);
  ck_assert_int_eq(model.vertexesCount, 8);
  ck_assert_int_eq(model.facesCount, 12);
  freeModel(&model);
}
END_TEST

START_TEST(case_7) {
  Model model;
  initModel(&model);
  int status = readModel(&model, "tests/dataset/no_model.txt");
  ck_assert_int_eq(status, ERROR_INCORRECT_FILE);
  freeModel(&model);
}
END_TEST

START_TEST(case_8) {
  Model model1, model2, model3;
  initModel(&model1);
  initModel(&model2);
  initModel(&model3);
  readModel(&model1, "tests/dataset/cringe_cube.txt");
  readModel(&model2, "tests/dataset/cringe_cube.txt");
  copyModel(&model1, &model3);

  ck_assert_int_eq(model2.vertexesCount, model3.vertexesCount);
  ck_assert_int_eq(model2.facesCount, model3.facesCount);
  for (int i = 0; i < model2.vertexesCount; i++) {
    ck_assert_double_eq(model2.vertexes[i], model3.vertexes[i]);
  }
  for (int i = 0; i < model2.facesCount; i++) {
    ck_assert_double_eq(model2.faces[i].vertexesCount,
                        model3.faces[i].vertexesCount);
    for (int j = 0; j < model2.faces[i].vertexesCount; j++) {
      ck_assert_int_eq(model2.faces[i].vertexes[j],
                       model3.faces[i].vertexes[j]);
    }
  }

  freeModel(&model1);
  freeModel(&model2);
  freeModel(&model3);
}
END_TEST

Suite *readModelSuite(void) {
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

  suite_add_tcase(s, tc);
  return s;
}
