/*
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

    FlowState Display::getState(int16_t value, boolean rightSide);
    void Display::rightSetBottom();
    void Display::rightSetTop();
    void Display::printToLedPanel();

  public:
    Display::Display(uint8_t pinClk, uint8_t pinDIO, int16_t lowThresholdValue, int16_t highThresholdValue, int16_t leftMaxValue);
    void Display::init();

    void Display::setBrightness(uint8_t value);
    void Display::setVisible(boolean targetState);
    // Update display and return possible settings change for encoder
    FlowState Display::getUpdate(int16_t value, boolean rightSide);
};

#endif /* DISPLAY_H */
