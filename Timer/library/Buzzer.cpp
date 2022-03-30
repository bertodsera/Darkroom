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

void Buzzer::init() {
  pinMode(_pin,OUTPUT);
}

void Buzzer::tic() {
  tone(_pin,5000);
  delay(50);
  noTone(_pin);
}

void Buzzer::storeSound() {
  for (int pitch=500; pitch <= 3000; pitch=pitch+25) {
    tone(_pin,pitch);
    delay(5);
    noTone(_pin);
  }
}
