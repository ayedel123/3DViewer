#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>

#include "../../gifRecorder/gifRecorderThread.h"
#include "../../utils/edges_counter.h"
#include "../../utils/utils.h"
#include "../glWindow/gl_window.h"
#include "../savingFile/GlWindowParamsSaver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  GlWindowParamsSaver *paramsSaver = new GlWindowParamsSaver();

  GLWindow *glWindow;

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_moveButton_clicked();

  void on_routButton_clicked();

  void on_scaleButton_clicked();

  void on_selectFileButton_clicked();

  void on_extraSetButton_clicked();

  void on_ribsSetButton_clicked();

  void on_vertexSetButton_clicked();

  void on_ribsColorButton_clicked();

  void on_vertexColorButton_clicked();

  void on_projectionSetButton_clicked();

  void on_backgroundColor_clicked();

  void on_backgroundSetButton_clicked();

  void on_renderButton_clicked();

  void on_renderJPEG_clicked();

  void on_renderBMP_clicked();

  void on_renderGIF_clicked();

  void on_ribsSize_textEdited(const QString &arg1);

  void on_vertexSize_textEdited(const QString &arg1);

  void on_vertexType_currentIndexChanged(int index);

  void on_ribsType_currentIndexChanged(int index);

  void on_projectionType_currentIndexChanged(int index);

  void on_moveSliderX_sliderMoved(int position);

  void on_moveSliderY_sliderMoved(int position);

  void on_moveSliderZ_sliderMoved(int position);

  void on_routSliderX_sliderMoved(int position);

  void on_routSliderY_sliderMoved(int position);

  void on_routSliderZ_sliderMoved(int position);

  void on_sacleSlider_sliderMoved(int position);

  void on_moveLineX_textChanged(const QString &arg1);

  void on_moveLineY_textChanged(const QString &arg1);

  void on_moveLineZ_textChanged(const QString &arg1);

  void on_routLineX_textChanged(const QString &arg1);

  void on_routLineY_textChanged(const QString &arg1);

  void on_routLineZ_textChanged(const QString &arg1);

  void on_scaleLine_textChanged(const QString &arg1);

 private:
  QLabel *infoLabel;
  Ui::MainWindow *ui;
  void initialization();
  void hideExtraSetLayout();

  void setParamsToOpenGlWidget();

  void processAndOpenModelFile(const QString &pathToFile);

  QVector4D processColorFromButton(QPushButton button);

  static QVector4D processColorFromButton(QPushButton *button);

  void infoLabelTextUpdate(int vertexesCount, int ribsCount,
                           const QString &filename);

  void stopRecordMessage();

  void startToRecordGifMessage();

  void getImageFromOpenGlWindow(const QString &);

  bool wantToSaveParams();

  void dropEvent(QDropEvent *event) override;

  void dragEnterEvent(QDragEnterEvent *event) override;

  void keyPressEvent(QKeyEvent *event) override;

  void keyReleaseEvent(QKeyEvent *event) override;

  void closeEvent(QCloseEvent *event) override;

  bool isCorrectModel(Model model);
};
#endif  // MAINWINDOW_H
