/*
 * PushButton.h
 *
 * Manage push button
 *
 * Author: berto.d.sera@gmail.com
 * Version 1.0
 *
 */

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "Arduino.h"

class PushButton {
  private:
    uint8_t       _pin;
    unsigned long _lastPressure = 0;

    boolean PushButton::isBeingPressedUnfiltered();
  public:
    PushButton::PushButton(uint8_t pin);
    boolean PushButton::isBeingPressed();
};

#endif /* PUSHBUTTON_H */
