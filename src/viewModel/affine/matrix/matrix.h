//
// Created by Turnip Sharee on 1/26/24.
//

#ifndef C8_3DVIEWER_V1_0_1_MATRIX_H
#define C8_3DVIEWER_V1_0_1_MATRIX_H
#ifdef __cplusplus
extern "C" {
#endif
#include "stdio.h"
#include "string.h"
void s21_clear_matrix(float *A);
void s21_mult_matrix(float *A, float *B, float *result);
void s21_mult_matrix4x1(float *A, float *B, float *result);
void copyMatrix4(float *src, float *dest);
void printMatrix(float *A);
void copyMatrix(float *src, float *dest);
#ifdef __cplusplus
}
#endif
#endif  // C8_3DVIEWER_V1_0_1_MATRIX_H
