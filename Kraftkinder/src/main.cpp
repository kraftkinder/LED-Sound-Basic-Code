// Neopixel Library
#include <Bounce.h>
#include <TaskScheduler.h>

// The LED Animations
#include "led_task.h"

// GPIO Buttons
const int buttonAPin = A15;
const int brightnessPotiPin = A17;

// Variables
const int numled = 156;
const int ledDataPin = 29;

byte drawingMemory[numled * 3];          //  3 bytes per LED
DMAMEM byte displayMemory[numled * 12];  // 12 bytes per LED

Bounce buttonA(buttonAPin, 100);

// Tasks
Scheduler scheduler;
LedStripTask ledStripTask(scheduler, numled, drawingMemory, displayMemory,
                          buttonAPin, brightnessPotiPin);

void setup() {
  // This is Teensy 4.1 specific
  pinMode(32, OUTPUT);
  digitalWrite(32, HIGH);

  // GPIO setup
  pinMode(buttonAPin, INPUT);

  // Start tasks
  ledStripTask.start();
}

void loop() {
  buttonA.update();
  if (buttonA.risingEdge()) {
    ledStripTask.nextState();
  }
  scheduler.execute();
}