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
    Switcher(uint8_t buttonPin, uint8_t ledPin);
    boolean poll();
    void setOn();
    void setOff();
    boolean isOn();

    // An ARCHIVE/RESTORE command used to manage the visibility of a switcher's object state.
    //   ON LEDs get switched off to be masked but keep their on state in memory
    //   Masked LEDs that return to visible state get switched back on according to their state in memory
    void setVisible(boolean targetState);

    void changeState();
};

#endif /* SWITCHER_H */
