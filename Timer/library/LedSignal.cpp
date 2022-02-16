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
