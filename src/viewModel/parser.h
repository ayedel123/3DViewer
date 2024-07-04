#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ctype.h>
#include <math.h>

#include "common.h"
int readModel(Model *model, char *fileName);

int fillModel(Model *model, int vertexesCount,
              int facesCount); /*Нужно очистить модель до вызова,создаёт массивы
вершин и поверхностей(память под вершины поврехности не выделяется)*/
void initModel(Model *model);  //просто заполняет нулями и null, использовать до
                               //работы с объектом структуры
void freeModel(Model *model);  //чистит

// Not for user
int analyzeFile(char *fileName, int *vertexesCount, int *facesCount);
int coolGetLine(char **line, int *lineMaxLength, FILE *file);
int parseVertexes(Model *model, int currentVertex, char *line);
int countVertexes(char *line);
int parseFaces(Model *model, int currentFace, int lastVertex, char *line);

#ifdef __cplusplus
}
#endif

#endif
