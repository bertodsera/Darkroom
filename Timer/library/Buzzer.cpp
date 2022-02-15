/*
 * Buzzer.cpp
 *
 * Manage Buzzer object
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#include "Arduino.h"
#include "Buzzer.h"

Buzzer::Buzzer( uint8_t pin ) {
  _pin = pin;
}

Buzzer::init() {
  pinMode(_pin,OUTPUT);
}

Buzzer::tic() {
  tone(_pin,50);
  delay(20);
  noTone(_pin);
}
