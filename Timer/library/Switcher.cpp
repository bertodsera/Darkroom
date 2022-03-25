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
 * Switcher.cpp
 *
 * Manage coupled PushButton and LedSignal Objects as a single entity
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#include "Arduino.h"
#include "Switcher.h"

Switcher::Switcher(uint8_t buttonPin, uint8_t ledPin) :
  _button(buttonPin),
  _led(ledPin) {}

boolean Switcher::poll() {
  return _button.isBeingPressed();
}

void Switcher::setOn() {
  _led.switchOn();
  _isOn = true;
}

void Switcher::setOff() {
  _led.switchOff();
  _isOn = false;
};

boolean Switcher::isOn() {
  return _isOn;
};

// An ARCHIVE/RESTORE command used to manage the visibility of a switcher's object state.
//   ON LEDs get switched off to be masked but keep their on state in memory
//   Masked LEDs that return to visible state get switched back on according to their state in memory
void Switcher::setVisible(boolean targetState) {
  if (_isOn) {
    if (targetState) { this->_led.switchOn(); }
    else { this->_led.switchOff(); }
  }
}


void Switcher::changeState() {
  if (this->isOn()) {
    this->setOff();
  } else {
    this->setOn();
  }
}
