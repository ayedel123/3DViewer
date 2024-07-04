#include "parser.h"

int isSuS(char c1, char c2) {
  int sus = 0;
  if (c1 == '\n') {
    if (c2 == 'v') {
      sus = 1;
    } else if (c2 == 'f') {
      sus = 2;
    }
  }
  return sus;
}

int analyzeFile(char *fileName, int *vertexesCount, int *facesCount) {
  FILE *file = fopen(fileName, "r");
  int statusCode = (file != NULL) ? SUCCESS : ERROR_MISSING_FILE;
  if (statusCode == SUCCESS) {
    *vertexesCount = 0;
    *facesCount = 0;
    char c1 = '\n', c2 = c1;
    int sus = 0;
    while (c2 != EOF) {
      c2 = fgetc(file);
      if (c2 == ' ' && sus) {
        if (sus == 1)
          (*vertexesCount)++;
        else if (sus == 2)
          (*facesCount)++;
      }
      sus = isSuS(c1, c2);
      c1 = c2;
    }
    fclose(file);
    if (*vertexesCount == 0 || *facesCount == 0) {
      statusCode = ERROR_INCORRECT_FILE;
    }
  }

  return statusCode;
}

int coolGetLine(char **line, int *lineMaxLength, FILE *file) {
  int statusCode = SUCCESS;
  if (file == NULL)
    statusCode = ERROR_MISSING_FILE;
  else {
    int i = 0;
    char c = '.';
    c = getc(file);
    while (c != '\n' && c != EOF && *line != NULL && statusCode == SUCCESS) {
      (*line)[i] = c;
      i++;
      if (i == *lineMaxLength - 1) {
        *lineMaxLength += *lineMaxLength;
        char *temp = realloc(*line, *lineMaxLength);
        if (temp != NULL) {
          *line = temp;
        } else {
          statusCode = ERROR_MEMORY;
        }
      }
      c = getc(file);
    }
    if (statusCode == SUCCESS) {
      (*line)[i] = '\0';
    }
    statusCode = (c == EOF) ? EOF : statusCode;
  }
  return statusCode;
}

void skipSpaces(char **line) {
  while (**line == ' ') {
    (*line)++;
  }
}
int eisdigit(char c) {
  if (isdigit(c) || c == '-')
    return 1;
  else
    return 0;
}

void skipNumbs(char **line) {
  while (eisdigit(**line)) {
    (*line)++;
  }
}

void setEdges(Model *model, int vertexId) {
  double *vertex = &(model->vertexes[vertexId]);
  if (vertex[0] > model->viewBox.right) model->viewBox.right = vertex[0];
  if (vertex[0] < model->viewBox.left) model->viewBox.left = vertex[0];
  if (vertex[1] > model->viewBox.top) model->viewBox.top = vertex[1];
  if (vertex[1] < model->viewBox.bottom) model->viewBox.bottom = vertex[1];

  if (vertex[2] > model->viewBox.front) model->viewBox.front = vertex[2];
  if (vertex[2] < model->viewBox.back) model->viewBox.back = vertex[2];
}

void setCenter(Model *model) {
  model->viewBox.center[0] = (model->viewBox.left + model->viewBox.right) / 2;
  model->viewBox.center[1] = (model->viewBox.top + model->viewBox.bottom) / 2;
  model->viewBox.center[2] = (model->viewBox.front + model->viewBox.back) / 2;
}

int parseVertexes(Model *model, int currentVertex, char *line) {
  line += 1;
  int statusCode = SUCCESS;
  char *endPtr = NULL;
  for (int i = 0; i < 3 && statusCode == SUCCESS; i++) {
    skipSpaces(&line);
    model->vertexes[currentVertex * 3 + i] = strtod(line, &endPtr);
    if (line == endPtr) {
      statusCode = ERROR_INCORRECT_FILE;
    }
    if (statusCode == SUCCESS) {
      setEdges(model, currentVertex * 3);
    }
    line = endPtr;
    endPtr = NULL;
  }

  return statusCode;
}

int islineOk(char *line) {
  char *charset = {"1234567890-/ \r"};
  int status = SUCCESS;
  while (*line != '\0' && status == SUCCESS) {
    if (strchr(charset, *line) == NULL) {
      status = ERROR_INCORRECT_FILE;
    }
    line++;
  }
  return status;
}
void skipUntilSpace(char **line) {
  while (**line != ' ' && **line != '\0') {
    (*line)++;
  }
}

int countVertexes(char *line) {
  if (islineOk(line) != SUCCESS) {
    return -1;
  }
  int i = 0;
  char *tmpLine = line;
  while (*line != '\0') {
    skipSpaces(&line);
    tmpLine = line;
    skipNumbs(&line);
    if (tmpLine != line) i++;
    skipUntilSpace(&line);
  }
  return i;
}

int parseFaces(Model *model, int currentFace, int lastVertex, char *line) {
  line++;
  int statusCode = SUCCESS;
  char *endPtr = NULL;
  int vertexesCount = countVertexes(line);
  long int tmpvertex = 0;
  if (vertexesCount < 1) statusCode = ERROR_INCORRECT_FILE;
  if (statusCode == SUCCESS) {
    statusCode = allocateFace(model, currentFace, vertexesCount);
    for (int i = 0; i < vertexesCount && *line != '\0' && statusCode == SUCCESS;
         i++) {
      skipUntilSpace(&line);
      skipSpaces(&line);
      tmpvertex = strtol(line, &endPtr, 10);
      if (tmpvertex < 0) {
        tmpvertex = lastVertex + tmpvertex + 1;
      }
      if (line == endPtr || tmpvertex > model->vertexesCount ||
          tmpvertex <= 0 || tmpvertex > INT32_MAX) {
        statusCode = ERROR_INCORRECT_FILE;
      }

      model->faces[currentFace].vertexes[i] = (int)tmpvertex - 1;
      line = endPtr;
      endPtr = NULL;
    }
    model->faces[currentFace].vertexesCount = vertexesCount;
  }
  return statusCode;
}

int readModel(Model *model, char *fileName) {
  int linesCount = -1;
  int lineMaxLength = 5;
  int vertexesCount = 0, facesCount = 0;

  int statusCode = analyzeFile(fileName, &vertexesCount, &facesCount);
  if (statusCode == SUCCESS) {
    int getLineStatus = SUCCESS;
    statusCode = fillModel(model, vertexesCount, facesCount);
    FILE *file = fopen(fileName, "r");
    char *line = calloc(sizeof(char), lineMaxLength);
    int currentVertex = 0;
    int currentFace = 0;

    linesCount = 0;
    while (getLineStatus == SUCCESS && statusCode == SUCCESS) {
      getLineStatus = coolGetLine(&line, &lineMaxLength, file);
      if (line[0] == 'v' && line[1] == ' ') {
        statusCode = parseVertexes(model, currentVertex, line);
        currentVertex++;
      } else if (line[0] == 'f' && line[1] == ' ') {
        statusCode = parseFaces(model, currentFace, currentVertex, line);
        currentFace++;
      }
      linesCount++;
    }
    fclose(file);
    free(line);

    if (statusCode == SUCCESS) setCenter(model);
    
  }
  return statusCode;
}
