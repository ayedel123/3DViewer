#ifndef CORES_H
#define CORES_H

#define ROTATE_ANGLE 50

#include <QVector3D>
#include <iostream>

struct CoresF {
 public:
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;

  CoresF(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  CoresF() {}

  void reset() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
  }

  static CoresF fromQVector3D(QVector3D qvector) {
    return {qvector.x(), qvector.y(), qvector.z()};
  }

  static QVector3D toQVector3D(CoresF cores) {
    return {cores.x, cores.y, cores.z};
  }

  static void print(CoresF cores) {
    std::cout << "CoresF<";
    std::cout << cores.x << " " << cores.y << " " << cores.z << ">\n";
  }
};

struct RotateParams {
  CoresF cores;
  CoresF angles;

  RotateParams() {
    angles = CoresF();
    cores = CoresF(1, 1, 1);
  }

  RotateParams(QVector3D coresVector, QVector3D anglesVector) {
    cores = CoresF::fromQVector3D(coresVector);
    angles = CoresF::fromQVector3D(anglesVector);
  }

  void reset() {
    angles.reset();
    cores.reset();
  }

  void setX(float x) {
    cores.x = 1;
    angles.x = x;
  }

  void setY(float y) {
    cores.y = 1;
    angles.y = y;
  }

  void setZ(float z) {
    cores.z = 1;
    angles.z = z;
  }
};

#endif  // CORES_H
