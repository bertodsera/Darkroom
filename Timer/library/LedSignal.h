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
