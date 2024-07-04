//
// Created by Turnip Sharee on 1/31/24.
//

#ifndef C8_3DVIEWER_V1_0_1_GIFRECORDER_H
#define C8_3DVIEWER_V1_0_1_GIFRECORDER_H

#include <iostream>

#include "../gifRecorder/gifEncoder/egif/GifEncoder.h"

class GifRecorder {
 public:
  GifRecorder();

  void addFrame(const uint8_t* image);

  void endAndSave();

  void start(const char* filename, int width, int height, int delay);

 private:
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t delay = 0;

  GifEncoder gifEncoder;
};

#endif  // C8_3DVIEWER_V1_0_1_GIFRECORDER_H
