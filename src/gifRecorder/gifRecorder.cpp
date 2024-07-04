#include "gifRecorder.h"

GifRecorder::GifRecorder() {
  width = 0;
  height = 0;
  delay = 0;
}

void GifRecorder::start(const char *filename, int width, int height,
                        int delay) {
  this->width = width;
  this->height = height;
  this->delay = delay;

  std::cout << "открытие GifRecorder::start "
            << gifEncoder.open(filename, width, height, 10, true, 0,
                               width * height * 3);
}

void GifRecorder::addFrame(const uint8_t *image) {
  gifEncoder.push(GifEncoder::PIXEL_FORMAT_RGB, (uint8_t *)image, width, height,
                  delay);
}

void GifRecorder::endAndSave() {
  std::cout << "gif saved status=" << gifEncoder.close() << "\n";
}
