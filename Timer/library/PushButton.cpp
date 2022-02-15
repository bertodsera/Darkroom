/*
 * PushButton.cpp
 *
 * Manage push button
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#include "Arduino.h"
#include "PushButton.h"

PushButton::PushButton(uint8_t pin) {
  _pin = pin;
  // avoid the need for a resistor by using the inbuilt pin resistor
  pinMode(_pin, INPUT_PULLUP);
}

// Simply say whether it's being pressed
boolean PushButton::isBeingPressedUnfiltered() {
  int buttonState = digitalRead(_pin);
  return (buttonState == LOW);
}

// Avoid double readings by setting a minimum interval of ~1 sec
//   between subsequent readings
boolean PushButton::isBeingPressed() {
  unsigned long currentTime = millis();
  if (this->isBeingPressedUnfiltered() && (currentTime - _lastPressure > 1000)) {
    _lastPressure = currentTime;
    return true;
  };
  return false;
}
