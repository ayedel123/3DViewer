

#ifndef C8_3DVIEWER_V1_0_1_AFFINE_H
#define C8_3DVIEWER_V1_0_1_AFFINE_H

#ifdef __cplusplus
extern "C" {
#endif
#include <math.h>

#include "../common.h"
#include "matrix/matrix.h"
typedef struct {
  float x;
  float y;
  float z;
  float w;
} Coordinate;

void translatef(float x, float y, float z, float *matrix);
void rotatef(float angle_x, float angle_y, float angle_z, float *matrix);
void scale(float x, float y, float z, float *matrix);
#endif  // C8_3DVIEWER_V1_0_1_AFFINE_H

#ifdef __cplusplus
}
#endif