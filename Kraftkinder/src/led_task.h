#include <TaskSchedulerDeclarations.h>
#include <WS2812Serial.h>

#include <vector>

#include "a_blue.h"
#include "a_red.h"
#include "ramp_b.h"
#include "ramp_g.h"
#include "ramp_r.h"

const int animationSize_red =
    sizeof animationData_red / sizeof animationData_red[0];
const int animationSize_blue =
    sizeof animationData_blue / sizeof animationData_blue[0];
const int animationSize_ramp_r =
    sizeof animationData_ramp_r / sizeof animationData_ramp_r[0];
const int animationSize_ramp_g =
    sizeof animationData_ramp_g / sizeof animationData_ramp_g[0];
const int animationSize_ramp_b =
    sizeof animationData_ramp_b / sizeof animationData_ramp_b[0];

class LedStripTask : public Task {
 public:
  LedStripTask(Scheduler& scheduler, int numled, byte* drawingMemory,
               byte* displayMemory, int ledDataPin, int brighnessPotiPin)
      : Task(&scheduler),
        leds_(numled, displayMemory, drawingMemory, ledDataPin, WS2812_GRB),
        brighnessPotiPin_(brighnessPotiPin) {
    pinMode(brighnessPotiPin, INPUT);
  }
  virtual ~LedStripTask() = default;

  bool Callback() final;
  void start();
  void stop();
  void nextState();

 private:
  /**
   * Get the poti's brightness in a range from 0 - 1023
   */
  int getBrightness();

  WS2812Serial leds_;

  int state_;
  const int totalStates_ = 2;
  /// The counter used to track the iterations for the active state
  int iterationCounter_;

  /// The pin connected to the poti controlling the LED brightness
  const int brighnessPotiPin_;
};
