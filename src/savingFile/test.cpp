//
// Created by Turnip Sharee on 2/7/24.
//

#include <QCoreApplication>
#include <iostream>

#include "SavingFile.h"

struct Params {
  int x;
  int y;
  int z;
};

int main() {
  QCoreApplication::setOrganizationName("org");
  QCoreApplication::setApplicationName("app");

  auto savingFile = new SavingFile();

  auto params = new Params();
  params->x = 0;
  params->y = 0;
  params->z = 0;

  auto value = QVariant::fromValue(params);

  savingFile->setValue(SavingFile::Key::LinesColor, value);

  auto gotValue = savingFile->get(SavingFile::Key::MoveCores).value<Params>();

  std::cout << gotValue.x;
}