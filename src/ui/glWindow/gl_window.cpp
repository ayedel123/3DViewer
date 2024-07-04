#include "gl_window.h"

GLint assertMinusOne(GLint number) {
  Q_ASSERT(number != -1);
  return number;
}

GLWindow::GLWindow(QWidget *parent) : QOpenGLWidget(parent) {
  setFixedSize(640, 480);
}

void GLWindow::initialize() {
  m_program = new QOpenGLShaderProgram(this);
  m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                     fragmentShaderSource);

  m_program->link();

  m_posAttr = assertMinusOne(m_program->attributeLocation("posAtr"));
  m_borderColor = assertMinusOne(m_program->uniformLocation("color"));
  m_matrixUniform = assertMinusOne(m_program->uniformLocation("matrix"));
  m_space = assertMinusOne(m_program->uniformLocation("space"));
  m_width = assertMinusOne(m_program->uniformLocation("width"));
  m_isDot = assertMinusOne(m_program->uniformLocation("_isDot"));
  m_verticeColor = assertMinusOne(m_program->uniformLocation("verticeColor"));
  m_drawVertices = assertMinusOne(m_program->uniformLocation("drawVertices"));

  retinaScale = devicePixelRatio();

  pixels =
      new unsigned char[width() * retinaScale * height() * retinaScale * 3];
}

void GLWindow::initializeGL() {
  initializeOpenGLFunctions();
  initialize();
}

void GLWindow::paintGL() {
  if (!_isModelSet) return;

  draw();

  glReadPixels(0, 0, width() * retinaScale, height() * retinaScale, GL_RGB,
               GL_UNSIGNED_BYTE, pixels);
}

void GLWindow::resizeGL(int w, int h) { glViewport(0, 0, width(), height()); }

void GLWindow::calculatePreMove() {
  preMove.x = +model->viewBox.center[0];
  preMove.y = -model->viewBox.center[1];
  preMove.z = -abs(model->viewBox.front) - abs(model->viewBox.back);
  float xoffset =
      tanf(viewAngle) * (model->viewBox.right - model->viewBox.center[0]);
  float yoffset = (model->viewBox.top - model->viewBox.center[1]);
  preMove.z = -1 - (model->viewBox.top - model->viewBox.center[1]);
  if (abs(model->viewBox.top - model->viewBox.bottom) >
      abs(model->viewBox.left - model->viewBox.right))
    preMove.z =
        -tan(viewAngle) * (abs(model->viewBox.top - model->viewBox.bottom));
  else
    preMove.z =
        -tan(viewAngle) * (abs(model->viewBox.right - model->viewBox.left));
  if (preMove.z > (model->viewBox.front))
    preMove.z = -1 - abs(model->viewBox.front);
}

void GLWindow::accessAffineTransformation() {
  float fmatrix[16] = {0};

  QMatrix4x4 matrix;

  if (typeOfProjection == PARALLEL_PROJECTION) {
    matrix.ortho(model->viewBox.left, model->viewBox.right,
                 model->viewBox.bottom, model->viewBox.top,
                 model->viewBox.front, model->viewBox.back);
  }

  else if (typeOfProjection == CENTRAL_PROJECTION) {
    matrix.perspective(viewAngle, (float)width() / (float)height(), 0.1,
                       (float)model->viewBox.back);
  }

  if (typeOfProjection == CENTRAL_PROJECTION) {
    matrix.translate(preMove.x, preMove.y, preMove.z);
  }

  copyQMatrix4x4ToFloatArray(matrix, fmatrix);

  translatef(_moveCores.x, _moveCores.y, _moveCores.z, fmatrix);
  rotatef(rotateParams.angles.x, rotateParams.angles.y, rotateParams.angles.z,
          fmatrix);
  scale(_scaleCores.x, _scaleCores.y, _scaleCores.z, fmatrix);

  copyFloatArrayToQMatrix4x4(fmatrix, matrix);
  m_program->setUniformValue(m_matrixUniform, matrix);
}

void GLWindow::accessParams() {
  m_program->setUniformValue(m_borderColor, colorOfBorders);
  m_program->setUniformValue(m_space, 10.0f);
  m_program->setUniformValue(m_width, widthOfLines);
  m_program->setUniformValue(m_isDot, _isDot);
  m_program->setUniformValue(m_drawVertices, false);
  m_program->setUniformValue(m_verticeColor, verticeColor);
  glLineWidth(widthOfLines);
}

void GLWindow::drawFaces() {
  for (int i = 0; i < model->facesCount; i++) {
    glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT, model->faces[i].vertexes);
  }
}

void GLWindow::drawVertices() {
  m_program->setUniformValue(m_drawVertices, true);
  m_program->setUniformValue(m_isDot, false);

  glPointSize(sizeOfVertices * 2);

  if (typeOfVertices == VERTICES_CIRCLES) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }

  glDrawArrays(GL_POINTS, 0, model->vertexesCount);

  m_program->setUniformValue(m_isDot, _isDot);
}

void GLWindow::drawBackground() {
  glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2],
               backgroundColor[3]);
  glClear(GL_COLOR_BUFFER_BIT);
}

void GLWindow::draw() {
  drawBackground();

  m_program->bind();

  accessAffineTransformation();
  accessParams();

  glVertexAttribPointer(m_posAttr, 3, GL_DOUBLE, GL_FALSE, 0, model->vertexes);
  glEnableVertexAttribArray(m_posAttr);

  drawFaces();
  if (typeOfVertices == VERTICES_CIRCLES || typeOfVertices == VERTICES_QUADS) {
    drawVertices();
  }

  glDisableVertexAttribArray(m_posAttr);
  m_program->release();
}

void GLWindow::wheelEvent(QWheelEvent *event) {
  auto delta = event->angleDelta();
  auto diffZ = (delta.y() / 15);

  if (keyControlPressed) {
    rotateByMouseX(diffZ);
  } else {
    moveByMouseZ(diffZ);
  }

  event->accept();
}

void GLWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == KEY_CONTROL) {
    keyControlPressed = true;
  }
  event->accept();
}

void GLWindow::keyReleaseEvent(QKeyEvent *event) {
  if (event->key() == KEY_CONTROL) {
    keyControlPressed = false;
  }
  event->accept();
}

void GLWindow::mousePressEvent(QMouseEvent *event) {
  mousePrevPos = event->pos();

  event->accept();
}

void GLWindow::mouseMoveEvent(QMouseEvent *event) {
  currentMousePos = event->pos();

  auto diffX = (currentMousePos.x() - mousePrevPos.x());
  auto diffY = (mousePrevPos.y() - currentMousePos.y());

  if (keyControlPressed) {
    rotateByMouseZY(diffX, diffY);
  } else {
    moveByMouseXY(diffX, diffY);
  }

  mousePrevPos = event->pos();

  event->accept();
}

void GLWindow::mouseDoubleClickEvent(QMouseEvent *event) {
  resetKeys();
  resetPosition();
  event->accept();
}

void GLWindow::setBackGroundColor(QVector4D color) {
  backgroundColor.setX(color.x());
  backgroundColor.setY(color.y());
  backgroundColor.setZ(color.z());
  update();
}

void GLWindow::setVerticesColor(QVector4D color) {
  verticeColor.setX(color.x());
  verticeColor.setY(color.y());
  verticeColor.setZ(color.z());
  update();
}

void GLWindow::setLinesColor(QVector4D color) {
  colorOfBorders.setX(color.x());
  colorOfBorders.setY(color.y());
  colorOfBorders.setZ(color.z());
  update();
}

void GLWindow::setScale(float a) {
  a = a * 0.1;
  _scaleCores.x = a;
  _scaleCores.y = a;
  _scaleCores.z = a;
  update();
}

void GLWindow::setSizeOfVertices(float newSizeOfVertices) {
  if (newSizeOfVertices < 0 || newSizeOfVertices > 200) {
    return;
  }

  sizeOfVertices = newSizeOfVertices;
  update();
}

void GLWindow::setTypeOfProjection(int newTypeOfProjection) {
  typeOfProjection = newTypeOfProjection;
  update();
}

void GLWindow::setTypeOfVertices(int newTypeOfVertices) {
  typeOfVertices = newTypeOfVertices;
  update();
}

void GLWindow::setIsDot(bool newIsDot) {
  _isDot = newIsDot;
  update();
}

void GLWindow::setWidthOfLines(float newWidthOfLines) {
  if (newWidthOfLines < 0) {
    widthOfLines = 0;
  } else {
    widthOfLines = newWidthOfLines;
  }

  update();
}

void GLWindow::setRotateX(float x) {
  rotateParams.setX(x);
  update();
}

void GLWindow::setRotateY(float y) {
  rotateParams.setY(y);
  update();
}

void GLWindow::setRotateZ(float z) {
  rotateParams.setZ(z);
  update();
}

void GLWindow::setMoveZ(float z) {
  _moveCores.z = z;
  update();
}

void GLWindow::setMoveY(float y) {
  _moveCores.y = y;
  update();
}

void GLWindow::setMoveX(float x) {
  _moveCores.x = x;
  update();
}

void GLWindow::setModel(Model *model1, const QString &pathToModel1) {
  _isModelSet = true;
  this->pathToModel = pathToModel1;
  initModel(model);
  copyModel(model1, this->model);
  calculatePreMove();
  update();
}

void GLWindow::setRotateParams(RotateParams _rotateParams) {
  setRotateX(_rotateParams.angles.x);
  setRotateY(_rotateParams.angles.y);
  setRotateZ(_rotateParams.angles.z);
}

void GLWindow::setScaleCorse(CoresF scaleCores) {
  _scaleCores.x = scaleCores.x;
  _scaleCores.y = scaleCores.y;
  _scaleCores.z = scaleCores.z;
}

void GLWindow::setMoveCores(CoresF moveCores) {
  setMoveX(moveCores.x);
  setMoveY(moveCores.y);
  setMoveZ(moveCores.z);
}

const RotateParams &GLWindow::getRotateParams() const { return rotateParams; }

const CoresF &GLWindow::getScaleCores() const { return _scaleCores; }

const CoresF &GLWindow::getMoveCores() const { return _moveCores; }

qreal GLWindow::getRetinaScale() const { return retinaScale; }

const QString &GLWindow::getPathToModel() const { return pathToModel; }

bool GLWindow::isDot() const { return _isDot; }

float GLWindow::getWidthOfLines() const { return widthOfLines; }

int GLWindow::getTypeOfVertices() const { return typeOfVertices; }

int GLWindow::getTypeOfProjection() const { return typeOfProjection; }

float GLWindow::getSizeOfVertices() const { return sizeOfVertices; }

const QVector4D &GLWindow::getColorOfBorders() const { return colorOfBorders; }

const QVector4D &GLWindow::getVerticeColor() const { return verticeColor; }

const QVector4D &GLWindow::getBackgroundColor() const {
  return backgroundColor;
}

void GLWindow::resetPosition() {
  rotateZ = rotateY = rotateX = 0;
  moveX = moveY = moveZ = 0;

  _moveCores.reset();
  rotateParams.reset();
  _scaleCores.x = 1;
  _scaleCores.y = 1;
  _scaleCores.z = 1;

  update();
}

void GLWindow::resetKeys() { keyControlPressed = false; }

void GLWindow::rotateByMouseZY(int diffX, int diffY) {
  if (abs(diffY) >= 2) {
    rotateZ += diffY;
    setRotateZ(rotateZ);
  }

  if (abs(diffX) >= 1) {
    rotateY += diffX;
    setRotateY(rotateY);
  }
}

void GLWindow::moveByMouseXY(int diffX, int diffY) {
  moveX += diffX;
  moveY += diffY;
  setMoveX(moveX * 0.01);
  setMoveY(moveY * 0.01);
}

void GLWindow::rotateByMouseX(int diffZ) {
  rotateX += diffZ;
  setRotateX(rotateX);
}

void GLWindow::moveByMouseZ(int diffZ) {
  moveZ += diffZ;
  setMoveZ(moveZ * 0.1);
}

bool GLWindow::isModelSet() const { return _isModelSet; }

void GLWindow::closeEvent(QCloseEvent *event) {
  freeModel(model);
  delete pixels;
  delete m_program;
}
