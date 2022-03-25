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
 * FunctionalUnit.h
 *
 * Manage a TM1637Display based LED Display Object
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#ifndef FUNCTIONALUNIT_H
#define FUNCTIONALUNIT_H

#include "Arduino.h"
#include <Display.h>
#include <Switcher.h>

class FunctionalUnit;

enum WhichButton { modeButton, sideButton, noButton};

class FunctionalUnit {
  private:
    Display  _ledDisplay;
    Switcher _mode;
    Switcher _side;
  public:
    FunctionalUnit (uint8_t pinClk, uint8_t pinDIO, int16_t lowThresholdValue, int16_t highThresholdValue, int16_t leftMaxValue,
                    uint8_t modeButtonPin, uint8_t modeLedPin,
                    uint8_t sideButtonPin, uint8_t sideLedPin);
    void init();

    void setBrightness(uint8_t value);

    // NOTE!! This returns whether ANY switcher button in the unit is being pressed,
    //   but it does NOT set the active state for the switcher!! The identity of the
    //   pressed button is passed back to the function caller, so it can be used.
    // enum WhichButton { modeButton, sideButton, noButton};
    WhichButton poll();

    // This does not alter any value in the unit, it only displays them, or not
    void setVisible( boolean targetState );

    // FlowState { countOverflow, withinBoundaries, countUnderflow, violationOfHighBoundary, violationOfLowBoundary, nonRelevant };
    FlowState updateLedDisplay (int16_t value, boolean rightSide);

    void modeChangeState();
    void sideChangeState();
};

#endif /* FUNCTIONALUNIT_H */
