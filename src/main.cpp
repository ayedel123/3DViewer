#include <QApplication>
#include <QLineEdit>
#include <QValidator>

#include "ui/mainWindow/mainwindow.h"

void setValidatorForLineEdits(QObject *parent) {
  QList<QLineEdit *> lineEdits = parent->findChildren<QLineEdit *>();
  for (QLineEdit *lineEdit : lineEdits) {
    auto *validator = new QDoubleValidator(lineEdit);
    lineEdit->setValidator(validator);
  }
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  w.resize(780, 480);
  setValidatorForLineEdits(&w);

  int x, y;
  x = w.screen()->availableSize().width() / 2 - w.width() / 2;
  y = w.screen()->availableSize().height() / 2 - w.height() / 2;
  w.move(x, y);

  return QApplication::exec();
}
