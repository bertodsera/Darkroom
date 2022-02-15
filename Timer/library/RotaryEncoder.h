/*
 * RotaryEncoder.h
 *
 * Manage Rotary Encoder Object
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include "Arduino.h"
#include <NewEncoder.h>

class RotaryEncoder {
  private:
    NewEncoder _encoder;
    int16_t    _value;
    int16_t    _minVal;
    int16_t    _maxVal;

  public:
    RotaryEncoder::RotaryEncoder(uint8_t aPin, uint8_t bPin, int16_t minValue, int16_t maxValue, int16_t initialValue, uint8_t type = FULL_PULSE);
    void RotaryEncoder::init ();

    boolean RotaryEncoder::pollValue ();
    boolean RotaryEncoder::newSettings(int16_t newMin, int16_t newMax, int16_t newCurrent);
    boolean RotaryEncoder::newValue(int16_t newCurrent);
    int16_t RotaryEncoder::getValue ();
};

#endif /* ROTARYENCODER_H */
