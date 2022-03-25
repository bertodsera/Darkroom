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
 * Display.h
 *
 * Manage a TM1637Display based LED Display Object
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "Arduino.h"
#include <TM1637Display.h>

class Display;

enum FlowState { countOverflow, withinBoundaries, countUnderflow, violationOfHighBoundary, violationOfLowBoundary, nonRelevant };

class Display {
  private:
    const TM1637Display _ledpanel;
    uint8_t _data[4];
    int16_t _right;
    int16_t _highThreshold; // top right value that makes an overflow (60 or 100)
    int16_t _lowThreshold;  // low right value that makes an underflow (-1)
    int16_t _left;
    int16_t _leftMax;       // top displayable left value (99)

    FlowState getState(int16_t value, boolean rightSide);
    void rightSetBottom();
    void rightSetTop();
    void printToLedPanel();

  public:
    Display(uint8_t pinClk, uint8_t pinDIO, int16_t lowThresholdValue, int16_t highThresholdValue, int16_t leftMaxValue);
    void init();

    void setBrightness(uint8_t value);
    void setVisible(boolean targetState);
    // Update display and return possible settings change for encoder
    FlowState getUpdate(int16_t value, boolean rightSide);
};

#endif /* DISPLAY_H */
