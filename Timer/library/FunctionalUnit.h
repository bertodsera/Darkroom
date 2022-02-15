/*
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
    FunctionalUnit::FunctionalUnit (uint8_t pinClk, uint8_t pinDIO, int16_t lowThresholdValue, int16_t highThresholdValue, int16_t leftMaxValue,
                                    uint8_t modeButtonPin, uint8_t modeLedPin,
                                    uint8_t sideButtonPin, uint8_t sideLedPin);
    void FunctionalUnit::init();

    void FunctionalUnit::setBrightness(uint8_t value);

    // NOTE!! This returns whether ANY switcher button in the unit is being pressed,
    //   but it does NOT set the active state for the switcher!! The identity of the
    //   pressed button is passed back to the function caller, so it can be used.
    // enum WhichButton { modeButton, sideButton, noButton};
    WhichButton FunctionalUnit::poll();

    // This does not alter any value in the unit, it only displays them, or not
    void FunctionalUnit::setVisible( boolean targetState );

    // FlowState { countOverflow, withinBoundaries, countUnderflow, violationOfHighBoundary, violationOfLowBoundary, nonRelevant };
    FlowState FunctionalUnit::updateLedDisplay (int16_t value, boolean rightSide);
};

#endif /* FUNCTIONALUNIT_H */
