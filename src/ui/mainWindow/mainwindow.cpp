#include "mainwindow.h"

#include <QKeyEvent>

#include "../../utils/cores.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setAcceptDrops(true);
  initialization();
}

MainWindow::~MainWindow() { delete ui; }

void hideLayout(QLayout* layout, bool isInit) {
  for (int i = 0; i < layout->count(); ++i) {
    QWidget* widget = layout->itemAt(i)->widget();
    if (widget) {
      if (isInit)
        widget->setVisible(false);
      else
        widget->setVisible(!widget->isVisible());
    }
  }
}

void hideMultLayout(QLayout* layout, QPushButton* button) {
  button->setVisible(!button->isVisible());
  hideLayout(layout, true);
}

void MainWindow::hideExtraSetLayout() {
  hideMultLayout(ui->ribsSetlLayout_2, ui->ribsSetButton);
  hideMultLayout(ui->vertexSetLayout_2, ui->vertexSetButton);
  hideMultLayout(ui->projectionSetLayout_2, ui->projectionSetButton);
  hideMultLayout(ui->backgroundSetLayout_2, ui->backgroundSetButton);
}

void MainWindow::initialization() {
  infoLabel = new QLabel(ui->openGLWidget);
  infoLabel->setText(" name: <br> vertices: <br> edges: ");
  infoLabel->setStyleSheet(
      "color: rgb(128, 128, 128); padding-left: 6px; padding-top: 3px;");
  auto sizePolicy = QSizePolicy();
  sizePolicy.setHorizontalPolicy(QSizePolicy::Expanding);
  infoLabel->setSizePolicy(sizePolicy);

  hideExtraSetLayout();
  hideLayout(ui->moveLayout_2, true);
  hideLayout(ui->routLayout_2, true);
  hideLayout(ui->scaleLayout_2, true);
  hideLayout(ui->renderLayout_2, true);
  ui->ribsSetButton->setVisible(false);
  ui->vertexSetButton->setVisible(false);
  ui->projectionSetButton->setVisible(false);
  ui->backgroundSetButton->setVisible(false);
  ui->filePath->setVisible(false);

  glWindow = ui->openGLWidget;

  if (paramsSaver->isSavedParamsExist()) setParamsToOpenGlWidget();
}

void MainWindow::closeEvent(QCloseEvent* event) {
  if (wantToSaveParams() && glWindow->isModelSet()) {
    paramsSaver->saveGlWindowParams(glWindow);
  } else {
    paramsSaver->clear();
  }

  glWindow->closeEvent(event);
}

void MainWindow::on_moveButton_clicked() {
  hideLayout(ui->moveLayout_2, false);
}

void MainWindow::on_routButton_clicked() {
  hideLayout(ui->routLayout_2, false);
}

void MainWindow::on_scaleButton_clicked() {
  hideLayout(ui->scaleLayout_2, false);
}

void MainWindow::on_extraSetButton_clicked() { hideExtraSetLayout(); }

void MainWindow::on_ribsSetButton_clicked() {
  hideLayout(ui->ribsSetlLayout_2, false);
}

void MainWindow::on_vertexSetButton_clicked() {
  hideLayout(ui->vertexSetLayout_2, false);
}

void MainWindow::on_projectionSetButton_clicked() {
  hideLayout(ui->projectionSetLayout_2, false);
}

void MainWindow::on_backgroundSetButton_clicked() {
  hideLayout(ui->backgroundSetLayout_2, false);
}

void MainWindow::on_renderButton_clicked() {
  hideLayout(ui->renderLayout_2, false);
}

void MainWindow::on_moveSliderX_sliderMoved(int position) {
  ui->moveLineX->setText(QString::number(position));
}

void MainWindow::on_moveSliderY_sliderMoved(int position) {
  ui->moveLineY->setText(QString::number(position));
}

void MainWindow::on_moveSliderZ_sliderMoved(int position) {
  ui->moveLineZ->setText(QString::number(position));
}

void MainWindow::on_routSliderX_sliderMoved(int position) {
  ui->routLineX->setText(QString::number(position));
}

void MainWindow::on_routSliderY_sliderMoved(int position) {
  ui->routLineY->setText(QString::number(position));
}

void MainWindow::on_routSliderZ_sliderMoved(int position) {
  ui->routLineZ->setText(QString::number(position));
}

void MainWindow::on_sacleSlider_sliderMoved(int position) {
  ui->scaleLine->setText(QString::number(position));
}
