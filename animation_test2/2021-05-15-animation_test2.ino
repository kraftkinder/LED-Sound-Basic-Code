#include "start.h"
#include "spray.h"
#include "red.h"
#include "green.h"
// #include "blue.h"
#include <WS2812Serial.h>

const int numled = 300;
const int pin = 29;

byte drawingMemory[numled * 3];       //  3 bytes per LED
DMAMEM byte displayMemory[numled * 12]; // 12 bytes per LED

WS2812Serial leds(numled, displayMemory, drawingMemory, pin, WS2812_GRB);

const int animationSize_start = sizeof animationData_start / sizeof animationData_start[0];
const int animationSize_spray = sizeof animationData_spray / sizeof animationData_spray[0];
const int animationSize_red = sizeof animationData_red / sizeof animationData_red[0];
const int animationSize_green = sizeof animationData_green / sizeof animationData_green[0];
// const int animationSize_blue = sizeof animationData_blue / sizeof animationData_blue[0];

void setup() {
  leds.begin();
  pinMode(32, OUTPUT);
  digitalWrite(32, HIGH);
  pinMode(A17, INPUT);
  pinMode(A15, INPUT);
}

void loop() {

  //start
  for (int k = 0; k < animationSize_start / (3 * leds.numPixels()); k++) {
    for (int i = 0; i < leds.numPixels() - 1; i++) {
      uint8_t red = animationData_start[3 * i + (k * leds.numPixels() * 3) + 0];
      uint8_t green = animationData_start[3 * i + (k * leds.numPixels() * 3) + 1];
      uint8_t blue = animationData_start[3 * i + (k * leds.numPixels() * 3) + 2];
      leds.setPixel(i, leds.Color(red, green, blue));
    }
    int poti = analogRead(A17);
    int bright_poti = poti / 4;
    leds.setBrightness(bright_poti);
    leds.show();

    int potiBlue = analogRead(A15);
    potiBlue = map(potiBlue, 0, 1023, 0, 50);
    delay(potiBlue); // 33 ms delay, 1/0.033 sind ungefähr 30 fps
  }

//spray
  for (int k = 0; k < animationSize_spray / (3 * leds.numPixels()); k++) {
    for (int i = 0; i < leds.numPixels() - 1; i++) {
      uint8_t red = animationData_spray[3 * i + (k * leds.numPixels() * 3) + 0];
      uint8_t green = animationData_spray[3 * i + (k * leds.numPixels() * 3) + 1];
      uint8_t blue = animationData_spray[3 * i + (k * leds.numPixels() * 3) + 2];
      leds.setPixel(i, leds.Color(red, green, blue));
    }
    int poti = analogRead(A17);
    int bright_poti = poti / 4;
    leds.setBrightness(bright_poti);
    leds.show();

    int potiBlue = analogRead(A15);
    potiBlue = map(potiBlue, 0, 1023, 0, 50);
    delay(potiBlue); // 33 ms delay, 1/0.033 sind ungefähr 30 fps
  }

  //red
  for (int k = 0; k < animationSize_red / (3 * leds.numPixels()); k++) {
    for (int i = 0; i < leds.numPixels() - 1; i++) {
      uint8_t red = animationData_red[3 * i + (k * leds.numPixels() * 3) + 0];
      uint8_t green = animationData_red[3 * i + (k * leds.numPixels() * 3) + 1];
      uint8_t blue = animationData_red[3 * i + (k * leds.numPixels() * 3) + 2];
      leds.setPixel(i, leds.Color(red, green, blue));
    }
    int poti = analogRead(A17);
    int bright_poti = poti / 4;
    leds.setBrightness(bright_poti);
    leds.show();
    delay(1); // 33 ms delay, 1/0.033 sind ungefähr 30 fps
  }

  //green
  for (int k = 0; k < animationSize_green / (3 * leds.numPixels()); k++) {
    for (int i = 0; i < leds.numPixels() - 1; i++) {
      uint8_t red = animationData_green[3 * i + (k * leds.numPixels() * 3) + 0];
      uint8_t green = animationData_green[3 * i + (k * leds.numPixels() * 3) + 1];
      uint8_t blue = animationData_green[3 * i + (k * leds.numPixels() * 3) + 2];
      leds.setPixel(i, leds.Color(red, green, blue));
    }
    int poti = analogRead(A17);
    int bright_poti = poti / 4;
    leds.setBrightness(bright_poti);
    leds.show();
    delay(1); // 33 ms delay, 1/0.033 sind ungefähr 30 fps
  }
/*
  //blue
  for (int k = 0; k < animationSize_blue / (3 * leds.numPixels()); k++) {
    for (int i = 0; i < leds.numPixels() - 1; i++) {
      uint8_t red = animationData_blue[3 * i + (k * leds.numPixels() * 3) + 0];
      uint8_t green = animationData_blue[3 * i + (k * leds.numPixels() * 3) + 1];
      uint8_t blue = animationData_blue[3 * i + (k * leds.numPixels() * 3) + 2];
      leds.setPixel(i, leds.Color(red, green, blue));
    }
    int poti = analogRead(A17);
    int bright_poti = poti / 4;
    leds.setBrightness(bright_poti);
    leds.show();
    delay(1); // 33 ms delay, 1/0.033 sind ungefähr 30 fps
  }
  */
}



/*

  void loop() {

  for (int k = 0; k < animationSize / (3 * leds.numPixels()); k++) {
   for (int i = 0; i < leds.numPixels() - 1; i++) {
     uint8_t red = animationData_red[3 * i + (k * leds.numPixels() * 3) + 0];
     uint8_t green = animationData_red[3 * i + (k * leds.numPixels() * 3) + 1];
     uint8_t blue = animationData_red[3 * i + (k * leds.numPixels() * 3) + 2];
     leds.setPixel(i, leds.Color(red, green, blue));
   }
   int poti = analogRead(A17);
   int bright_poti = poti/4;
   leds.setBrightness(bright_poti);
   int btn_onoff = digitalRead(A15);

  if (btn_onoff == HIGH) {
   // turn LED on:
   leds.show();
   }
   else{
     leds.clear();
     leds.show();
     break;
   }
   delay(50); // 33 ms delay, 1/0.033 sind ungefähr 30 fps
  }
  }

*/
