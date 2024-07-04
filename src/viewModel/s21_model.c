#include "common.h"

// void printModel(Model *model) {
//   for (int i = 0; i < model->vertexesCount*3; i+=3) {
//     printf("vertex %d:\n%lf %lf %lf\n", i/3, model->vertexes[i],
//            model->vertexes[i + 1], model->vertexes[i + 2]);
//   }
//   for (int i = 0; i < model->facesCount; i++) {
//     printf("face %d %d:\n", i, model->faces[i].vertexesCount);
//     for (int j = 0; j < model->faces[i].vertexesCount; j++) {
//       printf("%d ", model->faces[i].vertexes[j]);
//     }
//     printf("\n");
//   }
// }

// void printModelInfo(Model *model) {
//   printf("v %d f %d\n",model->vertexesCount,model->facesCount);
// }

// void printViewBox(Model *model) {
//   printf("Center: %lf %lf %lf\n", model->viewBox.center[0],
//          model->viewBox.center[1], model->viewBox.center[2]);
//   printf("l %lf r %lf\n", model->viewBox.left, model->viewBox.right);
//   printf("t %lf b %lf\n", model->viewBox.top, model->viewBox.back);
//   printf("f %lf b %lf\n", model->viewBox.front, model->viewBox.back);
// }

int allocateFace(Model *model, int curentFace, int vertexesCount) {
  int statusCode = SUCCESS;

  int *temp = calloc(sizeof(int *), vertexesCount);
  if (temp == NULL)
    statusCode = ERROR_MEMORY;
  else
    model->faces[curentFace].vertexes = temp;
  return statusCode;
}

int fillVertexes(Model *model, int vertexesCount) {
  int statusCode = SUCCESS;
  model->vertexes = calloc(sizeof(double *), vertexesCount * 3);
  if (model->vertexes == NULL) statusCode = ERROR_MEMORY;

  model->vertexesCount = vertexesCount;

  return statusCode;
}

int fillFaces(Model *model, int facesCount) {
  int statusCode = SUCCESS;
  model->faces = calloc(sizeof(Face), facesCount);
  if (model->faces == NULL)
    statusCode = ERROR_MEMORY;
  else {
    model->facesCount = facesCount;
    for (int i = 0; i < facesCount; i++) {
      model->faces[i].vertexes = NULL;
      model->faces[i].vertexesCount = 0;
    }
  }
  return statusCode;
}

int fillModel(Model *model, int vertexesCount, int facesCount) {
  int statusCode = 0;
  if (vertexesCount > 0) {
    statusCode = fillVertexes(model, vertexesCount);
  }
  if (facesCount > 0 && statusCode == SUCCESS) {
    statusCode = fillFaces(model, facesCount);
  }
  return statusCode;
}

void initViewBox(ViewBox *viewBox) {
  viewBox->top = DBL_MIN;
  viewBox->bottom = DBL_MAX;
  viewBox->right = DBL_MIN;
  viewBox->left = DBL_MAX;
  viewBox->center[0] = 0.0;
  viewBox->center[1] = 0.0;
  viewBox->center[2] = 0.0;
  viewBox->back = DBL_MAX;
  viewBox->front = DBL_MIN;
}

void initModel(Model *model) {
  model->faces = NULL;
  model->vertexes = NULL;
  model->facesCount = 0;
  model->vertexesCount = 0;
  initViewBox(&(model->viewBox));
}

void freeModel(Model *model) {
  if (model->vertexes != NULL) free(model->vertexes);

  for (int i = 0; i < model->facesCount; i++) {
    if (model->faces[i].vertexes != NULL) free(model->faces[i].vertexes);
  }
  if (model->faces != NULL) free(model->faces);
}

int copyModel(Model *src, Model *dest) {
  freeModel(dest);
  int statusCode = fillModel(dest, src->vertexesCount, src->facesCount);
  for (int i = 0; i < src->vertexesCount * 3 && statusCode == SUCCESS; i++) {
    dest->vertexes[i] = src->vertexes[i];
  }
  for (int i = 0; i < src->facesCount && statusCode == SUCCESS; i++) {
    statusCode = allocateFace(dest, i, src->faces[i].vertexesCount);
    for (int j = 0; j < src->faces[i].vertexesCount && statusCode == SUCCESS;
         j++) {
      dest->faces[i].vertexes[j] = src->faces[i].vertexes[j];
    }
    dest->faces[i].vertexesCount = src->faces[i].vertexesCount;
  }
  if (statusCode == SUCCESS) {
    dest->viewBox = src->viewBox;
  }
  return statusCode;
}
