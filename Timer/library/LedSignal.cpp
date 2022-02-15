/*
 * LedSignal.cpp
 *
 * Manage LED light object
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#include "Arduino.h"
#include "LedSignal.h"


LedSignal::LedSignal(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
}

void LedSignal::switchOn() {
  digitalWrite(_pin, HIGH);
}

void LedSignal::switchOff() {
  digitalWrite(_pin, LOW);
}
