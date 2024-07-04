//
// Created by Turnip Sharee on 2/2/24.
//

#ifndef C8_3DVIEWER_V1_0_1_GIFRECORDERTHREAD_H
#define C8_3DVIEWER_V1_0_1_GIFRECORDERTHREAD_H

#include <QImage>
#include <QThread>
#include <QTimer>

#include "gifRecorder.h"

class GifRecorderThread : public QObject {
  Q_OBJECT

  GifRecorder *gifRecorder;

  int width = 0;
  int height = 0;
  int delay = 10;

  int fps = 10;
  int framesAmount = 50;
  int sleepTime = 100;

 public:
  unsigned char **pixels;

  void setSize(int w, int h) {
    height = h;
    width = w;
  }

  void setGifParams(int fps1, int time) {
    fps = fps1;
    framesAmount = fps * time;
    sleepTime = 5 * 1000 / framesAmount;
    delay = sleepTime / 10;
  }

  void getFrame() {
    QImage image = QImage(*pixels, width, height, QImage::Format_RGB888);

    image.mirror();

    gifRecorder->addFrame(image.constBits());
  }

  void recording() {
    for (int i = 0; i < framesAmount; i++) {
      getFrame();
      QThread::msleep(sleepTime);
    }
  }

 public slots:
  void start() {
    gifRecorder = new GifRecorder();
    gifRecorder->start("gif1.gif", width, height, delay);
    recording();
    gifRecorder->endAndSave();
    QThread::currentThread()->quit();
  }
};

#endif  // C8_3DVIEWER_V1_0_1_GIFRECORDERTHREAD_H
