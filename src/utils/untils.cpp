#include <QMatrix4x4>
#include <QMessageBox>
#include <QWidget>
#include <iostream>

#include "utils.h"

QVector4D convertToQVector(QColor *color) {
  float x, y, z;

  color->getRgbF(&x, &y, &z);

  auto colorQVector = QVector4D();

  colorQVector.setX(x);
  colorQVector.setY(y);
  colorQVector.setZ(z);

  return reinterpret_cast<const QVector4D &>(colorQVector);
}

float stringToDouble(const QString &arg) {
  bool status;
  auto number = arg.toFloat(&status);

  if (!status) {
    return 0.0f;
  }

  return number;
}

char *castQStringToCharPointers(const QString &string) {
  QByteArray byteArray = string.toUtf8();
  char *charPointer = strdup(byteArray.constData());
  return charPointer;
}

void showMessage(QWidget *parent, const QString &text) {
  auto message = QMessageBox(parent);
  message.setText(text);
  message.exec();
}

void copyQMatrix4x4ToFloatArray(QMatrix4x4 &matrix, float *floatArray) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      floatArray[i * 4 + j] = matrix.constData()[i + j * 4];
    }
  }
}

void copyFloatArrayToQMatrix4x4(float *floatArray, QMatrix4x4 &matrix) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix.data()[i + j * 4] = floatArray[i * 4 + j];
    }
  }
}