// Neopixel Library
#include <WS2812Serial.h>

// The LED Animations
#include "a_red.h"
#include "a_blue.h"
#include "ramp_r.h"
#include "ramp_g.h"
#include "ramp_b.h"

// Variables
const int numled = 156;
const int pin = 29;
int buttonState;
int lastButtonState = HIGH;
int btnCounter = 0;
int reading;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

byte drawingMemory[numled * 3];       //  3 bytes per LED
DMAMEM byte displayMemory[numled * 12]; // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

const int animationSize_red = sizeof animationData_red / sizeof animationData_red[0];
const int animationSize_blue = sizeof animationData_blue / sizeof animationData_blue[0];
const int animationSize_ramp_r = sizeof animationData_ramp_r / sizeof animationData_ramp_r[0];
const int animationSize_ramp_g = sizeof animationData_ramp_g / sizeof animationData_ramp_g[0];
const int animationSize_ramp_b = sizeof animationData_ramp_b / sizeof animationData_ramp_b[0];

void setup() {
  leds.begin();

  // This is Teensy 4.1 specific
  pinMode(32, OUTPUT);
  digitalWrite(32, HIGH);

  // Defining the in- an outputs
  pinMode(A17, INPUT);
  pinMode(A15, INPUT);
}


void loop() {
  // Read the button's state
  reading = digitalRead(A15);

  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        btnCounter++;
      }
    }
  }

  // a Pushbutton toggles following the cases
  switch (btnCounter) {
    case 1 :
      for (int k = 0; k < animationSize_ramp_r / (3 * leds.numPixels()); k++) {
        for (int i = 0; i < leds.numPixels() - 1; i++) {
          uint8_t red = animationData_ramp_r[3 * i + (k * leds.numPixels() * 3) + 0];
          uint8_t green = animationData_ramp_r[3 * i + (k * leds.numPixels() * 3) + 1];
          uint8_t blue = animationData_ramp_r[3 * i + (k * leds.numPixels() * 3) + 2];
          leds.setPixel(i, leds.Color(red, green, blue));
        }
        int poti = analogRead(A17);
        int bright_poti = poti / 4;
        leds.setBrightness(bright_poti);
        leds.show();
        delay(15); // 33 ms delay, 1/0.033 sind ungefähr 30 fps
      }
      break;
    case 2:
      for (int k = 0; k < animationSize_ramp_g / (3 * leds.numPixels()); k++) {
        for (int i = 0; i < leds.numPixels() - 1; i++) {
          uint8_t red = animationData_ramp_g[3 * i + (k * leds.numPixels() * 3) + 0];
          uint8_t green = animationData_ramp_g[3 * i + (k * leds.numPixels() * 3) + 1];
          uint8_t blue = animationData_ramp_g[3 * i + (k * leds.numPixels() * 3) + 2];
          leds.setPixel(i, leds.Color(red, green, blue));
        }
        int poti = analogRead(A17);
        int bright_poti = poti / 4;
        leds.setBrightness(bright_poti);
        leds.show();
        delay(15); // 33 ms delay, 1/0.033 sind ungefähr 30 fps
      }
      break;
    default:
         for (int k = 0; k < animationSize_ramp_b / (3 * leds.numPixels()); k++) {
        for (int i = 0; i < leds.numPixels() - 1; i++) {
          uint8_t red = animationData_ramp_b[3 * i + (k * leds.numPixels() * 3) + 0];
          uint8_t green = animationData_ramp_b[3 * i + (k * leds.numPixels() * 3) + 1];
          uint8_t blue = animationData_ramp_b[3 * i + (k * leds.numPixels() * 3) + 2];
          leds.setPixel(i, leds.Color(red, green, blue));
        }
        int poti = analogRead(A17);
        int bright_poti = poti / 4;
        leds.setBrightness(bright_poti);
        leds.show();
        delay(15); // 33 ms delay, 1/0.033 sind ungefähr 30 fps
      }
      btnCounter = 0;
  }

  lastButtonState = reading;
}
