#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "debug.h"
#include "usbmsc.h"
#include "DynamicMtd.h"

#define NEOPIX 40u

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, NEOPIX, NEO_GRB + NEO_KHZ800);
uint32_t ledClear = 0;

#define LED_CLEAR_TIME 50

DynamicMtd testMtd;

void setup()
{
  DEBUG_BEGIN(115200);
  DBUGLN("======================================================");
  DBUGLN("USB MSC Test");
  DBUGLN("======================================================");

  strip.begin();
  strip.setPixelColor(0, 0, 0, 255);
  strip.show();

  MassStorage.addDevice(testMtd);
  MassStorage.onDataWrite([](size_t size) {
    strip.setPixelColor(0, 255, 0, 0);
    strip.show();
    ledClear = millis() + LED_CLEAR_TIME;
  });
  MassStorage.onDataRead([](size_t size) {
    strip.setPixelColor(0, 0, 255, 0);
    strip.show();
    ledClear = millis() + LED_CLEAR_TIME;
  });
}

void loop()
{
  MassStorage.poll();

  if(0 != ledClear && millis() > ledClear) {
    strip.setPixelColor(0, 0, 0, 255);
    strip.show();
  }
}