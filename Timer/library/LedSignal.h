/*
 * LedSignal.h
 *
 * Manage LED light object
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#ifndef LEDSIGNAL_H
#define LEDSIGNAL_H

#include "Arduino.h"

class LedSignal {
  private:
    uint8_t _pin;
  public:
    LedSignal::LedSignal(uint8_t pin);
    void LedSignal::switchOn();
    void LedSignal::switchOff();
};

#endif /* LEDSIGNAL_H */
