//
// Created by Turnip Sharee on 2/12/24.
//

#include "edges_counter.h"

#include <check.h>

#include "parser.h"

int edgesCounter(char *path) {
  Model model;
  readModel(&model, path);
  return countEdges(model);
}

START_TEST(test) {
  ck_assert_int_eq(edgesCounter("../src/tests/dataset/cubecarcas.txt"), 216);
  ck_assert_int_eq(edgesCounter("../src/tests/dataset/pyramid.txt"), 9);
  ck_assert_int_eq(edgesCounter("../src/tests/dataset/RightArrow.txt"), 36);
  ck_assert_int_eq(edgesCounter("../src/tests/dataset/tetrahedron.txt"), 126);
}
END_TEST

int main() {
  Suite *s1 = suite_create("Edges count");
  TCase *tc1_1 = tcase_create("Edges counter");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}