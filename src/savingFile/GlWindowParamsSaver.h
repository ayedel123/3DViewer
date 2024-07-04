//
// Created by Turnip Sharee on 2/7/24.
//

#ifndef C8_3DVIEWER_V1_0_1_GLWINDOWPARAMSSAVER_H
#define C8_3DVIEWER_V1_0_1_GLWINDOWPARAMSSAVER_H

#include "../ui/glWindow/gl_window.h"
#include "../utils/cores.h"
#include "SavingFile.h"

class GlWindowParamsSaver {
  SavingFile *savingFile = new SavingFile();

 public:
  RotateParams getRotateParams();

  CoresF getScaleCores();

  CoresF getMoveCores();

  QVector4D getBackgroundColor();

  int getVerticesType();

  bool getIsDot();

  int getProjectionType();

  QVector4D getLinesColor();

  QVector4D getVerticesColor();

  void saveScaleCores(CoresF scaleParams);

  void saveMoveCores(CoresF moveParams);

  void saveRotateParams(RotateParams rotateParams);

  void saveVerticesColor(QVector4D verticesColor);

  void saveBackgroundColor(QVector4D backgroundColor);

  void saveBorderColor(QVector4D linesColor);

  void saveProjectionType(int projectionType);

  void saveIsDotted(bool isDotted);

  void saveVerticesType(int verticesType);

  void savePathToModel(const QString &pathToModel);

  QString getPathToModel();

  void saveWidthOfLines(float d);

  void saveVerticesSize(float size);

  float getWidthOfLines();

  float getSizeOfVertices();

  bool isSavedParamsExist();

  void setSavedParamsExist();

  void clear();

  void saveGlWindowParams(GLWindow *glWindow);

  void setParamsToGlWindow(GLWindow *glWindow);

  void printAllParams();
};

#endif  // C8_3DVIEWER_V1_0_1_GLWINDOWPARAMSSAVER_H
