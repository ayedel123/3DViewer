//
// Created by Turnip Sharee on 2/7/24.
//

#include "SavingFile.h"

#include <iostream>

QVariant SavingFile::get(SavingFile::Key key) {
  auto path = QString("%1").arg(key);
  return settings.value(path);
}

void SavingFile::setValue(SavingFile::Key key, const QVariant& value) {
  auto path = QString("%1").arg(key);
  settings.setValue(path, value);
}

void SavingFile::clear() { settings.clear(); }
