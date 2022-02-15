#include <Arduino.h>
// Various debug services, uncomment to enable
#define _DEBUG

#include <TimerInterface.h>
TimerInterface userInterface;
  
void setup()
{
  Serial.begin(57600); // open the serial port at 57600 bps:
  Serial.println("Serial started");
  delay(500);
  userInterface.init();
}

void loop()
{
  userInterface.pollButtons();
  delay(100);
}
