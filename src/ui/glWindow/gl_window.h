#ifndef GL_WINDOW_H
#define GL_WINDOW_H

#include <stdio.h>

#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QGuiApplication>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QScreen>
#include <QtMath>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../../gifRecorder/gifRecorder.h"
#include "../../utils/cores.h"
#include "../../utils/utils.h"
#include "../../viewModel/affine/affine.h"
#include "../../viewModel/affine/matrix/matrix.h"
#include "../../viewModel/parser.h"

#define CENTRAL_PROJECTION 1
#define PARALLEL_PROJECTION 0

#define VERTICES_CIRCLES 0
#define VERTICES_QUADS 1
#define VERTICES_NOSHOWN 2

#define KEY_CONTROL 16777250
#define MINIMIZE_INCREASE1 0.1
#define MINIMIZE_INCREASE2 0.01

class GLWindow : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  GLWindow(QWidget *parent = nullptr);
  GLWindow();

  unsigned char *pixels;

  void setModel(Model *model, const QString &pathToModel1);
  void setWidthOfLines(float newWidthOfLines);
  void setBackGroundColor(QVector4D color);
  void setVerticesColor(QVector4D color);
  void setLinesColor(QVector4D color);
  void setIsDot(bool newIsDot);
  void setTypeOfVertices(int newTypeOfVertices);
  void setTypeOfProjection(int newTypeOfProjection);
  void setSizeOfVertices(float newSizeOfVertices);
  void setScale(float a);
  void setRotateX(float x);
  void setRotateY(float y);
  void setRotateZ(float z);
  void setMoveX(float x);
  void setMoveY(float y);
  void setMoveZ(float z);
  void setRotateParams(RotateParams params);
  void setScaleCorse(CoresF scaleCores_);
  void setMoveCores(CoresF moveCores);

  const RotateParams &getRotateParams() const;
  const CoresF &getScaleCores() const;
  const CoresF &getMoveCores() const;
  qreal getRetinaScale() const;
  const QString &getPathToModel() const;
  bool isDot() const;
  bool isModelSet() const;
  float getWidthOfLines() const;
  int getTypeOfVertices() const;
  int getTypeOfProjection() const;
  float getSizeOfVertices() const;
  const QVector4D &getColorOfBorders() const;
  const QVector4D &getVerticeColor() const;
  const QVector4D &getBackgroundColor() const;

  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void closeEvent(QCloseEvent *event) override;

 private:
  QOpenGLShaderProgram *m_program = nullptr;
  qreal retinaScale;
  Model *model = new Model();
  bool _isModelSet = false;

  RotateParams rotateParams;
  CoresF _scaleCores = CoresF(1, 1, 1);
  CoresF preMove = CoresF();
  CoresF _moveCores;

  QString pathToModel = nullptr;
  bool _isDot = false;
  float widthOfLines = 1;
  int typeOfVertices = VERTICES_NOSHOWN;
  int typeOfProjection = CENTRAL_PROJECTION;
  float sizeOfVertices = 1;
  QVector4D colorOfBorders =
      QVector4D(223.0 / 255, 115.0 / 255, 113.0 / 255, 1.0f);
  QVector4D verticeColor = QVector4D(1, 1, 1, 1.0f);
  float viewAngle = 45.0f;
  QVector4D backgroundColor =
      QVector4D(230.0 / 255, 226.0 / 255, 131.0 / 255, 1.0f);

  GLint m_posAttr = 0;
  GLint m_borderColor = 0;
  GLint m_matrixUniform = 0;
  GLint m_space = 0;
  GLint m_width = 0;
  GLint m_isDot = 0;
  GLint m_verticeColor = 0;
  GLint m_drawVertices = 0;

  QPoint mousePrevPos;
  QPoint currentMousePos;
  bool keyControlPressed;
  int moveX = 0;
  int moveY = 0;
  int rotateX = 0;
  int rotateZ;
  int rotateY = 0;
  int moveZ = 0;

  void initialize();

  void draw();
  void drawBackground();
  void drawFaces();
  void drawVertices();
  void accessParams();
  void accessAffineTransformation();
  void calculatePreMove();

  void resetPosition();
  void rotateByMouseZY(int diffX, int diffY);
  void rotateByMouseX(int diffZ);
  void moveByMouseXY(int diffX, int diffY);
  void moveByMouseZ(int diffZ);

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;

  void resetKeys();

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
};

static const char *vertexShaderSource =
    "attribute highp vec4 posAtr ;\n"
    "uniform highp mat4 matrix;\n"
    "void main() {\n"
    "   gl_Position = matrix * posAtr;\n"

    "}\n";

static const char *fragmentShaderSource =
    "uniform highp vec4 color;\n"
    "uniform vec4 verticeColor;\n"
    "uniform float space;\n"
    "uniform float width;\n"
    "uniform bool _isDot;\n"
    "uniform bool drawVertices;"
    "void main() {\n"
    "    bool t1 = fract((gl_FragCoord.x + gl_FragCoord.z + gl_FragCoord.y) / "
    "space) > width/space;\n"
    "    if (_isDot && t1)\n"
    "    {"
    "        discard;"
    "    }\n"
    "    if (drawVertices){\n"
    "       gl_FragColor = verticeColor;\n"
    "    } else {\n"
    "        gl_FragColor = color;\n"
    "    }\n"
    "}\n";

#endif  // GL_WINDOW_H
