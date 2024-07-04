//
// Created by Turnip Sharee on 2/8/24.
//

#ifndef C8_3DVIEWER_V1_0_1_UNTILS_H
#define C8_3DVIEWER_V1_0_1_UNTILS_H

#include <QColor>

#include "cores.h"

QVector4D convertToQVector(QColor *color);

float stringToDouble(const QString &arg);

char *castQStringToCharPointers(const QString &string);

void showMessage(QWidget *parent, const QString &text);

CoresF convertToColorF(QColor color);

void copyQMatrix4x4ToFloatArray(QMatrix4x4 &matrix, float *floatArray);

void copyFloatArrayToQMatrix4x4(float *floatArray, QMatrix4x4 &matrix);

#endif  // C8_3DVIEWER_V1_0_1_UNTILS_H
