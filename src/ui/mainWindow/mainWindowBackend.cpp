#include <QDropEvent>
#include <QMimeData>
#include <QProcess>

#include "mainwindow.h"
#include "ui_mainwindow.h"

QColor colorSelect(QWidget *widget) {
  QColorDialog dialog;
  QColor color;
  color.setRgb(0, 0, 0);
  QPoint buttonPos = widget->mapToGlobal(QPoint(0, 0));
  dialog.move(buttonPos);

  if (dialog.exec()) {
    color = dialog.selectedColor();
  }

  return color;
}

void MainWindow::setParamsToOpenGlWidget() {
  processAndOpenModelFile(paramsSaver->getPathToModel());
  paramsSaver->setParamsToGlWindow(glWindow);
  glWindow->update();
}

void MainWindow::infoLabelTextUpdate(int vertexesCount, int ribsCount,
                                     const QString &filename) {
  infoLabel->setText(QString(" name: <n> <br> vertices: <v> <br> edges: <r>")
                         .replace("<v>", QString::number(vertexesCount))
                         .replace("<r>", QString::number(ribsCount))
                         .replace("<n>", filename));

  infoLabel->adjustSize();
}

void MainWindow::processAndOpenModelFile(const QString &pathToFile) {
  Model model;

  int status = readModel(&model, castQStringToCharPointers(pathToFile));

  if (status == SUCCESS && isCorrectModel(model)) {
    ui->openGLWidget->setModel(&model, pathToFile);
    infoLabelTextUpdate(model.vertexesCount, countEdges(model),
                        pathToFile.split("/").last());

    ui->filePath->setText(pathToFile);
    ui->filePath->setVisible(true);

  } else {
    QMessageBox::critical(nullptr, "Ошибка", "Не возможно прочитать файл");
  }
}
//  Выбор файла
void MainWindow::on_selectFileButton_clicked() {
  QString str;

  QString startPath = QDir::currentPath();
  str = QFileDialog::getOpenFileName(this, "Выбрать файл", startPath, "(*)");

  processAndOpenModelFile(str);
}

QVector4D MainWindow::processColorFromButton(QPushButton *button) {
  auto color = colorSelect(button);
  ;
  auto colorQVector = convertToQVector(&color);
  return reinterpret_cast<const QVector4D &>(colorQVector);
}

// выбор цвета для ребер вершин и фона
void MainWindow::on_ribsColorButton_clicked() {
  ui->openGLWidget->setLinesColor(processColorFromButton(ui->ribsColorButton));
}

void MainWindow::on_vertexColorButton_clicked() {
  ui->openGLWidget->setVerticesColor(
      processColorFromButton(ui->vertexColorButton));
}

void MainWindow::on_backgroundColor_clicked() {
  ui->openGLWidget->setBackGroundColor(
      processColorFromButton(ui->backgroundColor));
}

void MainWindow::getImageFromOpenGlWindow(const QString &name) {
  auto image = QImage(
      glWindow->pixels, glWindow->width() * glWindow->getRetinaScale(),
      glWindow->height() * glWindow->getRetinaScale(), QImage::Format_RGB888);
  image.mirror();

  const auto &path_to_save = name;

  auto status = image.save(path_to_save);

  if (status) {
    showMessage(this, name + " saved");
  } else {
    showMessage(this, name + " not saved");
  }
}

void MainWindow::on_renderJPEG_clicked() {
  getImageFromOpenGlWindow("screen.jpeg");
}

void MainWindow::on_renderBMP_clicked() {
  getImageFromOpenGlWindow("screen.bmp");
}

void MainWindow::on_renderGIF_clicked() {
  auto *rec = new GifRecorderThread();

  rec->setSize(glWindow->width() * glWindow->getRetinaScale(),
               glWindow->height() * glWindow->getRetinaScale());

  auto timerThread = new QThread();

  rec->pixels = &ui->openGLWidget->pixels;

  rec->moveToThread(timerThread);

  startToRecordGifMessage();

  connect(timerThread, SIGNAL(started()), rec, SLOT(start()));

  connect(timerThread, &QThread::finished, this,
          &MainWindow::stopRecordMessage);

  timerThread->start();

  // delete timerThread;
  // delete rec;
}

void MainWindow::startToRecordGifMessage() {
  ui->renderGIF->setText("recording...");
  update();
}

void MainWindow::stopRecordMessage() {
  showMessage(this, "gif saved");
  ui->renderGIF->setText("Рендер в GIF");
}

// измениние размера ребер и вершин
void MainWindow::on_ribsSize_textEdited(const QString &arg1) {
  ui->openGLWidget->setWidthOfLines(stringToDouble(arg1));
}

void MainWindow::on_vertexSize_textEdited(const QString &arg1) {
  ui->openGLWidget->setSizeOfVertices(stringToDouble(arg1));
}

// изменение в выпадающем списке типа
void MainWindow::on_vertexType_currentIndexChanged(int index) {
  ui->openGLWidget->setTypeOfVertices(index);
}

void MainWindow::on_ribsType_currentIndexChanged(int index) {
  if (index == 0) {
    ui->openGLWidget->setIsDot(false);
  } else {
    ui->openGLWidget->setIsDot(true);
  }
}

void MainWindow::on_projectionType_currentIndexChanged(int index) {
  ui->openGLWidget->setTypeOfProjection(index);
}

//перемещение
void MainWindow::on_moveLineX_textChanged(const QString &arg1) {
  ui->openGLWidget->setMoveX(stringToDouble(arg1));
}

void MainWindow::on_moveLineY_textChanged(const QString &arg1) {
  ui->openGLWidget->setMoveY(stringToDouble(arg1));
}

void MainWindow::on_moveLineZ_textChanged(const QString &arg1) {
  ui->openGLWidget->setMoveZ(stringToDouble(arg1));
}

//кручение
void MainWindow::on_routLineX_textChanged(const QString &arg1) {
  ui->openGLWidget->setRotateX(stringToDouble(arg1));
}

void MainWindow::on_routLineY_textChanged(const QString &arg1) {
  ui->openGLWidget->setRotateY(stringToDouble(arg1));
}

void MainWindow::on_routLineZ_textChanged(const QString &arg1) {
  ui->openGLWidget->setRotateZ(stringToDouble(arg1));
}

//масштабирование
void MainWindow::on_scaleLine_textChanged(const QString &arg1) {
  ui->openGLWidget->setScale(stringToDouble(arg1));
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
  if (event->mimeData()->hasUrls()) {
    event->acceptProposedAction();
  }
}

void MainWindow::dropEvent(QDropEvent *event) {
  const QMimeData *mimeData = event->mimeData();
  processAndOpenModelFile(mimeData->text().sliced(7));
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  glWindow->keyPressEvent(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
  glWindow->keyReleaseEvent(event);
}

bool MainWindow::wantToSaveParams() {
  auto saveButton = QMessageBox::StandardButton::Yes;
  auto notSaveButton = QMessageBox::StandardButton::Cancel;
  auto result = QMessageBox::question(this, "", "Сохранить настройки",
                                      notSaveButton, saveButton);
  return result == saveButton;
}

bool MainWindow::isCorrectModel(Model model) {
  return model.vertexesCount > 0 && model.facesCount > 0 &&
         model.faces != nullptr && model.vertexes != nullptr;
}
