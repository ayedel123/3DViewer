#include "matrix.h"

void s21_mult_matrix(float *A, float *B, float *result) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      result[i * 4 + j] = 0;
      for (int k = 0; k < 4; k++) {
        result[i * 4 + j] += A[i * 4 + k] * B[k * 4 + j];
      }
    }
  }
}

void s21_clear_matrix(float *A) { memset(A, 0, 16 * sizeof(A[0])); }

// void printMatrix(float *A) {

//   for (int i = 0; i < 16; i++) {
//     printf("%.7f ", A[i]);
//     if ((i + 1) % 4 == 0)
//       putchar('\n');
//   }
//   putchar('\n');
// }

void copyMatrix(float *src, float *dest) {
  for (int i = 0; i < 16; i++) {
    dest[i] = src[i];
  }
}
