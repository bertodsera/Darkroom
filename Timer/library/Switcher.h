/*
 * Switcher.h
 *
 * Manage coupled PushButton and LedSignal Objects as a single entity
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#ifndef SWITCHER_H
#define SWITCHER_H

#include "Arduino.h"
#include <PushButton.h>
#include <LedSignal.h>

class Switcher {
  private:
    PushButton _button;
    LedSignal  _led;
    boolean    _isOn = false;

  public:
    Switcher::Switcher(uint8_t buttonPin, uint8_t ledPin);
    boolean Switcher::poll();
    void Switcher::setOn();
    void Switcher::setOff();
    boolean Switcher::isOn();

    // An ARCHIVE/RESTORE command used to manage the visibility of a switcher's object state.
    //   ON LEDs get switched off to be masked but keep their on state in memory
    //   Masked LEDs that return to visible state get switched back on according to their state in memory
    void Switcher::setVisible(boolean targetState);
};

#endif /* SWITCHER_H */
