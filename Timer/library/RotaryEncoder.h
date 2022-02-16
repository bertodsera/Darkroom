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
