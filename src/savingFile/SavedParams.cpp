//
// Created by Turnip Sharee on 2/7/24.
//

#include <QVector4D>

#include "GlWindowParamsSaver.h"

CoresF GlWindowParamsSaver::getScaleCores() {
  return CoresF::fromQVector3D(
      savingFile->get(SavingFile::ScaleParams).value<QVector3D>());
}

CoresF GlWindowParamsSaver::getMoveCores() {
  return CoresF::fromQVector3D(
      savingFile->get(SavingFile::MoveCores).value<QVector3D>());
}

RotateParams GlWindowParamsSaver::getRotateParams() {
  return {savingFile->get(SavingFile::RotateParams).value<QVector3D>(),
          savingFile->get(SavingFile::RotateParamsAngle).value<QVector3D>()};
}

QVector4D GlWindowParamsSaver::getBackgroundColor() {
  return savingFile->get(SavingFile::BackgroundColor).value<QVector4D>();
}

QVector4D GlWindowParamsSaver::getVerticesColor() {
  return savingFile->get(SavingFile::VerticesColor).value<QVector4D>();
}

QVector4D GlWindowParamsSaver::getLinesColor() {
  return savingFile->get(SavingFile::LinesColor).value<QVector4D>();
}

int GlWindowParamsSaver::getProjectionType() {
  return savingFile->get(SavingFile::Key::ProjectionType).value<int>();
}

bool GlWindowParamsSaver::getIsDot() {
  return savingFile->get(SavingFile::IsDotted).value<bool>();
}

int GlWindowParamsSaver::getVerticesType() {
  return savingFile->get(SavingFile::VerticesType).value<int>();
}

QString GlWindowParamsSaver::getPathToModel() {
  return savingFile->get(SavingFile::PathToModel).value<QString>();
}

float GlWindowParamsSaver::getWidthOfLines() {
  return savingFile->get(SavingFile::WidthLines).value<float>();
}

float GlWindowParamsSaver::getSizeOfVertices() {
  return savingFile->get(SavingFile::VerticesSize).value<float>();
}

void GlWindowParamsSaver::saveScaleCores(CoresF scaleParams) {
  savingFile->setValue(SavingFile::ScaleParams,
                       QVariant::fromValue(CoresF::toQVector3D(scaleParams)));
}

void GlWindowParamsSaver::saveMoveCores(CoresF moveParams) {
  return savingFile->setValue(
      SavingFile::MoveCores,
      QVariant::fromValue(CoresF::toQVector3D(moveParams)));
}

void GlWindowParamsSaver::saveRotateParams(RotateParams rotateParams) {
  auto angles = QVariant::fromValue(CoresF::toQVector3D(rotateParams.angles));
  auto cores = QVariant::fromValue(CoresF::toQVector3D(rotateParams.cores));
  savingFile->setValue(SavingFile::RotateParamsAngle, angles);

  savingFile->setValue(SavingFile::RotateParams, cores);
}

void GlWindowParamsSaver::saveBackgroundColor(QVector4D backgroundColor) {
  return savingFile->setValue(SavingFile::BackgroundColor,
                              QVariant::fromValue(backgroundColor));
}

void GlWindowParamsSaver::saveVerticesColor(QVector4D verticesColor) {
  return savingFile->setValue(SavingFile::VerticesColor,
                              QVariant::fromValue(verticesColor));
}

void GlWindowParamsSaver::saveBorderColor(QVector4D linesColor) {
  return savingFile->setValue(SavingFile::LinesColor,
                              QVariant::fromValue(linesColor));
}

void GlWindowParamsSaver::saveProjectionType(int projectionType) {
  return savingFile->setValue(SavingFile::ProjectionType,
                              QVariant::fromValue(projectionType));
}

void GlWindowParamsSaver::saveIsDotted(bool isDotted) {
  return savingFile->setValue(SavingFile::IsDotted,
                              QVariant::fromValue(isDotted));
}

void GlWindowParamsSaver::saveVerticesType(int verticesType) {
  return savingFile->setValue(SavingFile::VerticesType,
                              QVariant::fromValue(verticesType));
}

void GlWindowParamsSaver::savePathToModel(const QString &pathToModel) {
  return savingFile->setValue(SavingFile::PathToModel,
                              QVariant::fromValue(pathToModel));
}

void GlWindowParamsSaver::saveWidthOfLines(float width) {
  return savingFile->setValue(SavingFile::WidthLines,
                              QVariant::fromValue(width));
}

void GlWindowParamsSaver::saveVerticesSize(float size) {
  return savingFile->setValue(SavingFile::VerticesSize,
                              QVariant::fromValue(size));
}

void GlWindowParamsSaver::clear() { savingFile->clear(); }

bool GlWindowParamsSaver::isSavedParamsExist() {
  return !savingFile->get(SavingFile::ParamsWasSaved).isNull();
}

void GlWindowParamsSaver::setSavedParamsExist() {
  savingFile->setValue(SavingFile::ParamsWasSaved, QVariant::fromValue(true));
}

void GlWindowParamsSaver::saveGlWindowParams(GLWindow *glWindow) {
  savePathToModel(glWindow->getPathToModel());
  saveIsDotted(glWindow->isDot());
  saveWidthOfLines(glWindow->getWidthOfLines());
  saveVerticesType(glWindow->getTypeOfVertices());
  saveProjectionType(glWindow->getTypeOfProjection());
  saveVerticesSize(glWindow->getSizeOfVertices());
  saveBorderColor(glWindow->getColorOfBorders());
  saveVerticesColor(glWindow->getVerticeColor());
  saveBackgroundColor(glWindow->getBackgroundColor());
  saveScaleCores(glWindow->getScaleCores());
  saveMoveCores(glWindow->getMoveCores());
  saveRotateParams(glWindow->getRotateParams());
  setSavedParamsExist();
}

void GlWindowParamsSaver::setParamsToGlWindow(GLWindow *glWindow) {
  glWindow->setIsDot(getIsDot());
  glWindow->setWidthOfLines(getWidthOfLines());
  glWindow->setTypeOfVertices(getVerticesType());
  glWindow->setTypeOfProjection(getProjectionType());
  glWindow->setSizeOfVertices(getSizeOfVertices());
  glWindow->setLinesColor(getLinesColor());
  glWindow->setVerticesColor(getVerticesColor());
  glWindow->setBackGroundColor(getBackgroundColor());
  glWindow->setRotateParams(getRotateParams());
  glWindow->setScaleCorse(getScaleCores());
  glWindow->setMoveCores(getMoveCores());
}

void GlWindowParamsSaver::printAllParams() {
  qDebug() << getIsDot();
  qDebug() << getWidthOfLines();
  qDebug() << getVerticesType();
  qDebug() << getProjectionType();
  qDebug() << getSizeOfVertices();
  qDebug() << getLinesColor();
  qDebug() << getVerticesColor();
  qDebug() << getBackgroundColor();
  CoresF::print(getRotateParams().angles);
  qDebug();
  CoresF::print(getRotateParams().cores);
  qDebug();
  CoresF::print(getScaleCores());
  qDebug();
  CoresF::print(getMoveCores());
  qDebug();
}
