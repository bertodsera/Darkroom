/*
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
