#include "led_task.h"

void LedStripTask::start() {
  setIterations(-1);
  enable();
}

void LedStripTask::stop() { disable(); }

void LedStripTask::nextState() {
  state_++;
  iterationCounter_ = 0;
  forceNextIteration();
}

bool LedStripTask::Callback() {
  int k = iterationCounter_;
  switch (state_) {
    case 0:
      if (k >= animationSize_ramp_r / (3 * leds_.numPixels())) {
        iterationCounter_ = 0;
      }
      for (int i = 0; i < leds_.numPixels() - 1; i++) {
        uint8_t red =
            animationData_ramp_r[3 * i + (k * leds_.numPixels() * 3) + 0];
        uint8_t green =
            animationData_ramp_r[3 * i + (k * leds_.numPixels() * 3) + 1];
        uint8_t blue =
            animationData_ramp_r[3 * i + (k * leds_.numPixels() * 3) + 2];
        leds_.setPixel(i, leds_.Color(red, green, blue));
      }
      leds_.setBrightness(getBrightness());
      leds_.show();
      this->delay(15);
      break;
    case 1:
      if (k >= animationSize_ramp_g / (3 * leds_.numPixels())) {
        iterationCounter_ = 0;
      }
      for (int i = 0; i < leds_.numPixels() - 1; i++) {
        uint8_t red =
            animationData_ramp_g[3 * i + (k * leds_.numPixels() * 3) + 0];
        uint8_t green =
            animationData_ramp_g[3 * i + (k * leds_.numPixels() * 3) + 1];
        uint8_t blue =
            animationData_ramp_g[3 * i + (k * leds_.numPixels() * 3) + 2];
        leds_.setPixel(i, leds_.Color(red, green, blue));
      }
      leds_.setBrightness(getBrightness());
      leds_.show();
      // 33 ms delay, 1/0.033 sind ungefähr 30 fps. Delay task and do not
      // sleep loop thread
      this->delay(15);
      break;
    case 2:
      if (k >= animationSize_ramp_b / (3 * leds_.numPixels())) {
        iterationCounter_ = 0;
      }
      for (int i = 0; i < leds_.numPixels() - 1; i++) {
        uint8_t red =
            animationData_ramp_b[3 * i + (k * leds_.numPixels() * 3) + 0];
        uint8_t green =
            animationData_ramp_b[3 * i + (k * leds_.numPixels() * 3) + 1];
        uint8_t blue =
            animationData_ramp_b[3 * i + (k * leds_.numPixels() * 3) + 2];
        leds_.setPixel(i, leds_.Color(red, green, blue));
      }
      leds_.setBrightness(getBrightness());
      leds_.show();
      // 33 ms delay, 1/0.033 sind ungefähr 30 fps. Delay task and do not
      // sleep loop thread
      this->delay(15);
      break;
    default:
      state_ = 0;
      forceNextIteration();
  }
  iterationCounter_++;
  return true;
}

int LedStripTask::getBrightness() {
  return analogRead(brighnessPotiPin_) / 4;
}