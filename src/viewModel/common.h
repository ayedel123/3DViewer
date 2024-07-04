#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define ERROR_MISSING_FILE 1
#define ERROR_INCORRECT_FILE 2
#define ERROR_MEMORY 3

typedef struct Face {
  int *vertexes;
  int vertexesCount;
} Face;

typedef struct ViewBox {
  double top;
  double bottom;
  double right;
  double left;
  double center[3];
  double front;
  double back;
} ViewBox;

typedef struct Model {
  double *vertexes;
  int vertexesCount;
  Face *faces;
  int facesCount;

  ViewBox viewBox;

} Model;

void freeModel(Model *model);
void initModel(Model *model);
void initViewBox(ViewBox *viewBox);
int fillModel(Model *model, int vertexesCount, int facesCount);
int fillFaces(Model *model, int facesCount);
int fillVertexes(Model *model, int vertexesCount);
void printViewBox(Model *model);
void printModel(Model *model);
int allocateFace(Model *model, int curentFace, int vertexesCount);
int copyModel(Model *src, Model *dest);
void printModelInfo(Model *model);
void freeModel(Model *model);

#ifdef __cplusplus
}
#endif

#endif