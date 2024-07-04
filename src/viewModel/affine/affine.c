
#include "affine.h"

void makeTranslatef(float x, float y, float z, float *A) {
  memset(A, 0, 16 * sizeof(float));
  A[3] = x;
  A[7] = y;
  A[11] = z;
  A[0] = 1.0f;
  A[5] = 1.0f;
  A[10] = 1.0f;
  A[15] = 1.0f;
}

void translatef(float x, float y, float z, float *matrix) {
  float A[16], B[16];
  makeTranslatef(x, y, z, A);
  s21_mult_matrix(matrix, A, B);
  memcpy(matrix, B, 16 * sizeof(float));
}

void makeRotatefX(float *A, float angle) {
  memset(A, 0, sizeof(float) * 16);
  A[0] = 1.0f;
  A[5] = cosf(angle);
  A[6] = -sinf(angle);
  A[9] = sinf(angle);
  A[10] = cosf(angle);
  A[15] = 1.0f;
}
void makeRotatefY(float *A, float angle) {
  memset(A, 0, sizeof(float) * 16);
  A[0] = cosf(angle);
  A[2] = sinf(angle);
  A[5] = 1.0f;
  A[8] = -sinf(angle);
  A[10] = cosf(angle);
  A[15] = 1.0f;
}
void makeRotatefZ(float *A, float angle) {
  memset(A, 0, sizeof(float) * 16);
  A[0] = cosf(angle);
  A[1] = -sinf(angle);
  A[4] = sinf(angle);
  A[5] = cosf(angle);
  A[10] = 1.0f;
  A[15] = 1.0f;
}

void rotatef(float angle_x, float angle_y, float angle_z, float *matrix) {
  angle_x = angle_x * M_PI / 180.0;
  angle_y = angle_y * M_PI / 180.0;
  angle_z = angle_z * M_PI / 180.0;

  float temp[16], result[16];
  makeRotatefX(temp, angle_x);
  s21_mult_matrix(matrix, temp, result);
  memcpy(matrix, result, 16 * sizeof(float));

  makeRotatefY(temp, angle_y);
  s21_mult_matrix(matrix, temp, result);
  memcpy(matrix, result, 16 * sizeof(float));

  makeRotatefZ(temp, angle_z);
  s21_mult_matrix(matrix, temp, result);
  memcpy(matrix, result, 16 * sizeof(float));
}

// void rotatef(float angle_x, float angle_y, float angle_z, float *matrix) {
//   angle_x = angle_x * M_PI / 180.0;
//   angle_y = angle_y * M_PI / 180.0;
//   angle_z = angle_z * M_PI / 180.0;
//   float temp[16], result[16];
//   // if (x >= 0) {
//   makeRotatefX(temp, angle_x);
//   s21_mult_matrix(temp, matrix, result);
//   copyMatrix(result, matrix);
//   // }
//   // if (y >= 0) {
//   // makeRotatefY(temp, angle_y);
//   // s21_mult_matrix(temp, matrix, result);
//   // copyMatrix(result, matrix);
//   // // }
//   // // if (z >= 0) {
//   // makeRotatefZ(temp, angle_z);
//   // s21_mult_matrix(temp, matrix, result);
//   // copyMatrix(result, matrix);
//   // }
// }

// void rotatef(Coordinate *cord,float angle, float *matrix) {
//     float A[16], B[16];
//     makeRotatefX(A, angle);
//     s21_mult_matrix(A, matrix, B);
//     copyMatrix(B,matrix);
//     makeRotatefY(A, angle);
//     copyMatrix(B,matrix);
//     s21_mult_matrix(A, matrix, B);
//     makeRotatefZ(A, angle);
//     copyMatrix(B,matrix);
//     s21_mult_matrix(A, matrix, B);
//     copyMatrix(B,matrix);
// }

void makeScale(float x, float y, float z, float *A) {
  s21_clear_matrix(A);
  A[0] = x;
  A[5] = y;
  A[10] = z;
  A[15] = 1.0f;
}

void scale(float x, float y, float z, float *matrix) {
  float A[16], B[16], C[16];

  makeScale(x, y, z, B);  // создаем матрицу масштабирования
  copyMatrix(matrix, A);  // копируем исходную матрицу

  // Умножаем исходную матрицу на матрицу масштаба
  s21_mult_matrix(A, B, C);

  // Копируем результат обратно в исходную матрицу
  copyMatrix(C, matrix);
}

void glRotatef(float angle, float x, float y, float z);
void glRotated(double angle, double x, double y, double z);

void glScalef(float x, float y, float z);
void glScaled(double x, double y, double z);
