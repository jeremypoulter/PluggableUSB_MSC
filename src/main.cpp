#include <Arduino.h>

#include "usbmsc.h"
#include "debug.h"

void setup()
{
  DEBUG_BEGIN(115200);
  DBUGLN("======================================================");
  DBUGLN("USB MSC Test");
  DBUGLN("======================================================");
}

void loop()
{
  if (0 == (millis() % 1000)) {
   // DBUGLN("Alive!");
  }
}