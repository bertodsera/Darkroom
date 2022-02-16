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
 * FunctionalUnit.cpp
 *
 * Manage a TM1637Display based LED Display Object
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#include "Arduino.h"
#include "FunctionalUnit.h"


FunctionalUnit::FunctionalUnit (uint8_t pinClk, uint8_t pinDIO, int16_t lowThresholdValue, int16_t highThresholdValue, int16_t leftMaxValue,
                                uint8_t modeButtonPin, uint8_t modeLedPin,
                                uint8_t sideButtonPin, uint8_t sideLedPin) :
  _ledDisplay(pinClk, pinDIO, lowThresholdValue, highThresholdValue, leftMaxValue),
  _mode(modeButtonPin, modeLedPin),
  _side(sideButtonPin, sideLedPin)
{}

void FunctionalUnit::init() {
  _ledDisplay.init();
}

void FunctionalUnit::setBrightness(uint8_t value) {
  _ledDisplay.setBrightness(value);
}

// NOTE!! This returns whether ANY switcher button in the unit is being pressed,
//   but it does NOT set the active state for the switcher!! The identity of the
//   pressed button is passed back to the function caller, so it can be used.
// enum WhichButton { modeButton, sideButton, noButton};
WhichButton FunctionalUnit::poll() {
  if (_mode.poll()) { return modeButton; }
  else if (_side.poll()) { return sideButton; }
  else { return noButton; }
}

// This does not alter any value in the unit, it only displays them, or not
void FunctionalUnit::setVisible( boolean targetState ) {
  _ledDisplay.setVisible(targetState);
  _mode.setVisible(targetState);
  _side.setVisible(targetState);
}

// FlowState { countOverflow, withinBoundaries, countUnderflow, violationOfHighBoundary, violationOfLowBoundary, nonRelevant };
FlowState FunctionalUnit::updateLedDisplay (int16_t value, boolean rightSide) {
  FlowState state = _ledDisplay.getUpdate(value, rightSide);
  #ifdef _DEBUG
    Serial.println("... ... TimerInterface::updateFromEncoder");
    Serial.println();
  #endif
  return state;
}
