/*
 * =======================================================================================================================
 * This file is part of Darkroom.
 * Darkroom is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Darkroom is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with Darkroom.
 * If not, see <https://www.gnu.org/licenses/>.
 * =======================================================================================================================
 *
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
