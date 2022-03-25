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
 * PushButton.h
 *
 * Manage push button
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "Arduino.h"

class PushButton {
  private:
    uint8_t       _pin;
    unsigned long _lastPressure = 0;

    boolean isBeingPressedUnfiltered();
  public:
    PushButton(uint8_t pin);
    boolean isBeingPressed();
};

#endif /* PUSHBUTTON_H */
