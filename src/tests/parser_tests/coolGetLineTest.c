#include "../backTests.h"

START_TEST(empty_file) {
  int lineMaxLen = 255;
  int oldLen = lineMaxLen;
  char *line = calloc(sizeof(char), lineMaxLen);

  FILE *file = fopen("tests/dataset/empty.txt", "r");
  int status = coolGetLine(&line, &lineMaxLen, file);
  fclose(file);
  free(line);
  ck_assert_int_eq(status, EOF);
  ck_assert_int_eq(oldLen, lineMaxLen);
}
END_TEST

START_TEST(some_test) {
  int lineMaxLen = 15;
  int oldLen = lineMaxLen;
  int status = SUCCESS;
  char *line = calloc(sizeof(char), lineMaxLen);
  char data[][30] = {"p.i.v.o", "123", "1LONGLINE__123456789", "v 0 1 2",
                     "f 1"};
  FILE *file = fopen("cool_data.txt", "w+");
  if (file != NULL) {
    for (int i = 0; i < 5; i++) {
      fprintf(file, data[i]);
      fputc('\n', file);
    }
    fclose(file);
    FILE *file = fopen("cool_data.txt", "r\n");
    for (int i = 0; i < 5; i++) {
      status = coolGetLine(&line, &lineMaxLen, file);
      ck_assert_str_eq(line, data[i]);
      ck_assert_int_eq(status, SUCCESS);
      if (i == 2) {
        ck_assert_int_gt(lineMaxLen, oldLen);
      }
    }
    status = coolGetLine(&line, &lineMaxLen, file);
    ck_assert_int_eq(status, EOF);
    fclose(file);
  }
  remove("cool_data.txt");
  free(line);
}
END_TEST

Suite *coolGetLineSuite(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("Cool get line");
  tc = tcase_create("test");

  tcase_add_test(tc, empty_file);
  tcase_add_test(tc, some_test);
  suite_add_tcase(s, tc);
  return s;
}
