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
 * TimerInterface.cpp
 *
 * Timer's Interface Object
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#include "Arduino.h"
#include "TimerInterface.h"


TimerInterface::TimerInterface() :
  // Init array of Display objects according to their constructor
  // Display::Display(uint8_t pinClk, uint8_t pinDIO, int lowThreshold, int highThreshold, int leftMaxValue) :
  _functionalUnit{ FunctionalUnit(TIMERCLK,  TIMERDIO,  TIMERENCODERMIN, TIMERENCODERMAX, ENCODERLEFTMAX,
                                  TIMERMODEBUTTONPIN, TIMERMODEBUTTONLED,
                                  TIMERSIDEBUTTONPIN, TIMERSIDEBUTTONLED),
                   FunctionalUnit(SOURCECLK, SOURCEDIO, SIZEENCODERMIN,  SIZEENCODERMAX,  ENCODERLEFTMAX,
                                  SOURCEMODEBUTTONPIN, SOURCEMODEBUTTONLED,
                                  SOURCESIDEBUTTONPIN, SOURCESIDEBUTTONLED),
                   FunctionalUnit(TARGETCLK, TARGETDIO, SIZEENCODERMIN,  SIZEENCODERMAX,  ENCODERLEFTMAX,
                                  TARGETMODEBUTTONPIN, TARGETMODEBUTTONLED,
                                  TARGETSIDEBUTTONPIN, TARGETSIDEBUTTONLED) },
    _encoderObj(ROTARYENCODERPINA, ROTARYENCODERPINB, TIMERENCODERMIN, TIMERENCODERMAX, TIMERENCODERSTART, FULL_PULSE),
    _execute(EXECUTEBUTTONPIN),
    _brightness(BRIGHTNESSBUTTONPIN, BRIGHTNESSBUTTONLED),
    _encoderButton(ENCODEREBUTTONPIN),
    _sound(BEEPER) {};

void TimerInterface::init() {
  Serial.println("Starting Displays ");
  for(int k=0; k <= 2; k++) {
    Serial.print("  Display: ");
    Serial.println(k);
    _functionalUnit[k].init();
  }
  // _encoderObj.init();
}

void TimerInterface::setBrightness(uint8_t value) {
  for(int k=0; k <= 2; k++) {
    _functionalUnit[k].setBrightness(value);
  }
};

// enum WhichButton { modeButton, sideButton, noButton};
void TimerInterface::pollButtons () {
  WhichButton whichPressed = noButton;
  for (int k=0; k <= 2; k++) {
    whichPressed = _functionalUnit[k].poll();
    if (whichPressed != noButton) {
      // manage the button pressure
      _sound.tic();
      #ifdef _DEBUG
        Serial.println("... ... TimerInterface::pollButtons");
        if (k==TIMER_UI) {
          Serial.print("... ... ... TIMER ");
          if (whichPressed==modeButton) { Serial.println("mode");
          } else { Serial.println("side"); };

        } else if (k==SOURCE_UI) {
          Serial.print("... ... ... SOURCE ");
          if (whichPressed==modeButton) { Serial.println("mode");
          } else { Serial.println("side"); };

        } else if (k==TARGET_UI) {
          Serial.print("... ... ... TARGET ");
          if (whichPressed==modeButton) {Serial.println("mode");
          } else { Serial.println("side"); };
        };
        Serial.println("======================================================");
      #endif
    };
  };
}


// This function updates the display and returns information on potential
//   further operations to be performed on the encoder object
//   ref: FlowState { countOverflow, withinBoundaries, countUnderflow, violationOfHighBoundary, violationOfLowBoundary, nonRelevant };
void TimerInterface::updateFromEncoder (uint8_t target, boolean rightSide) {
  // Act only if there's a new value
  if (_encoderObj.pollValue()) {
    int16_t value = _encoderObj.getValue();
    FlowState state = _functionalUnit[target].updateLedDisplay(value, rightSide);

    #ifdef _DEBUG
      Serial.println("... ... TimerInterface::updateFromEncoder");
      Serial.println();
    #endif

    // Manage the encoder, if any modificagtion is needed
    if ((state == countOverflow) || (state == violationOfLowBoundary)) {
      // setting right counter on its min legal value
      if (target == TIMER_UI) {
        _encoderObj.newValue(TIMERENCODERMIN + 1);
      } else {
        _encoderObj.newValue(SIZEENCODERMIN + 1);
      }
    } else if ((state == countUnderflow) || (state == violationOfHighBoundary)) {
      // setting right counter on its top legal value
      if (target == TIMER_UI) {
        _encoderObj.newValue(TIMERENCODERMAX - 1);
      } else {
        _encoderObj.newValue(SIZEENCODERMAX - 1);
      }
    };
    #ifdef _DEBUG
      Serial.println("===============================================================");
    #endif
  };
}

// enum FocusTarget { timerUI, sourceUI, targetUI, brightnessUI };
void TimerInterface::focusEncoderOn (FocusTarget destination, boolean rightSide) {
  _focus = destination;

  // input from encoder, output on timer LED panel, format hh:mm or mm:ss
  //   source and destination panels are off
  if (destination==timerUI) {
    if (rightSide) {
    } else {
    }
  // input from encoder, output on target LED panel, format in mm., from 0 to 9999 (~10m)
  //   timer is off
  //   source and destination are on
  } else if (destination==sourceUI) {
    if (rightSide) {
    } else {
    }
  // input from encoder, output on target LED panel, format in mm., from 0 to 9999 (~10m)
  //   timer is off
  //   source and destination are on
  } else if (destination==targetUI) {
    if (rightSide) {
    } else {
    }
  // input from encoder, output on LED panels' brightness
  //   timer, source and destination are on
  //   rightSide is meaningless for this context
  } else if (destination==brightnessUI) {
  };
}
