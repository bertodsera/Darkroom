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
 * TimerInterface.h
 *
 * Timer's Interface Object
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#ifndef TIMERINTERFACE_H
#define TIMERINTERFACE_H

#include "Arduino.h"
#include <Buzzer.h>
#include <FunctionalUnit.h>
#include <RotaryEncoder.h>
#include <Configuration.h>

class TimerInterface;

enum FocusTarget { timerUI, sourceUI, targetUI, brightnessUI };

class TimerInterface {
  private:
    FunctionalUnit _functionalUnit[3];
    RotaryEncoder  _encoderObj;
    FocusTarget   _focus = timerUI;
    boolean       _rightSegment = true;
    PushButton    _execute;
    Switcher      _brightness;
    PushButton    _encoderButton;
    Buzzer        _sound;

  public:
    TimerInterface();
    void init();

    void setBrightness(uint8_t value);

    // enum WhichButton { modeButton, sideButton, noButton};
    void pollButtons ();


    // This function updates the display and returns information on potential
    //   further operations to be performed on the encoder object
    //   ref: FlowState { countOverflow, withinBoundaries, countUnderflow, violationOfHighBoundary, violationOfLowBoundary, nonRelevant };
    void updateFromEncoder (uint8_t target, boolean rightSide);

    // enum FocusTarget { timerUI, sourceUI, targetUI, brightnessUI };
    FocusTarget whichIsActive( int index );
    void focusEncoderOn (FocusTarget destination, boolean rightSide = true);

    // Exposure
    void expose();
};

#endif /* TIMERINTERFACE_H */
