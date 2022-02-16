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
 * Display.cpp
 *
 * Manage a TM1637Display based LED Display Object
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#include "Arduino.h"
#include "Display.h"

// Describe what's trying to happen.
// This is used to spot and manage cases in which a boundary is being overstepped
// Ref. FlowState { countOverflow, withinBoundaries, countUnderflow, violationOfHighBoundary, violationOfLowBoundary, nonRelevant };
FlowState Display::getState(int16_t value, boolean rightSide) {
  // intercept attempted boundary violation
  if ((_left == _leftMax) && (value == _highThreshold)) { return violationOfHighBoundary; }
  if ((_left == _lowThreshold + 1) && (value == _lowThreshold)) { return violationOfLowBoundary; }

  // manage over and underflow
  if (rightSide) {
    if (value == _highThreshold) { return countOverflow; }
    else if (value == _lowThreshold) { return countUnderflow; }
    else { return withinBoundaries; };

  // Left side here
  } else {
    // only top boundary used for left pair
    return nonRelevant;
  };
}

void Display::rightSetBottom() {
  _right = _lowThreshold + 1;
}

void Display::rightSetTop() {
  _right = _highThreshold - 1;
}

void Display::printToLedPanel() {
  _ledpanel.showNumberDecEx(_left*100+_right, 0xff, true);
}

Display::Display(uint8_t pinClk, uint8_t pinDIO, int16_t lowThresholdValue, int16_t highThresholdValue, int16_t leftMaxValue) :
  _ledpanel( pinClk, pinDIO),
  _data { 0x00, 0x00, 0x00, 0x00 }
{
  _lowThreshold  = lowThresholdValue;
  _highThreshold = highThresholdValue;
  _leftMax       = leftMaxValue;
  this->rightSetBottom();
  _left          = _right;
}

void Display::init() {
  Serial.println("    Display starting...");
  #ifdef _DEBUG
    Serial.println("... ... Display::init");
    Serial.print("... ... ... lowThreshold: ");
    Serial.println(_lowThreshold);
    Serial.print("... ... ... highThreshold: ");
    Serial.println(_highThreshold);
    Serial.print("... ... ... leftMax: ");
    Serial.println(_leftMax);
    Serial.print("... ... ... right: ");
    Serial.println(_right);
    Serial.print("... ... ... left: ");
    Serial.println(_left);
    delay(1000);
  #endif
  _ledpanel.setBrightness(0x0f);
  // Change all digits to zero, at right, then left
  this->getUpdate(0,true);
  this->getUpdate(0,false);
  this->printToLedPanel();
}

void Display::setBrightness(uint8_t value) {
  _ledpanel.setBrightness(value);
  _ledpanel.setSegments(_data);
}

// TODO!!!
void Display::setVisible(boolean targetState) {};

// Update display and return possible settings change for encoder
// enum FlowState { countOverflow, withinBoundaries, countUnderflow, violationOfHighBoundary, violationOfLowBoundary, nonRelevant };
// TODO Check this code, unlikely to work as is for a left section
FlowState Display::getUpdate(int16_t value, boolean rightSide) {
  FlowState state = this->getState(value, rightSide);
  #ifdef _DEBUG
    Serial.println("... ... Display::getUpdate");
    Serial.print("... ... ... value: ");
    Serial.println(value);
    Serial.print("... ... ... rightSide: ");
    if (rightSide) { Serial.println("*"); }
    else { Serial.println(); }
    // countOverflow, withinBoundaries, countUnderflow, nonRelevant
    Serial.print("... ... ... state: ");
    if (state == countOverflow) { Serial.println("countOverflow"); }
    else if (state == withinBoundaries) { Serial.println("withinBoundaries"); }
    else if (state == countUnderflow) { Serial.println("countUnderflow"); }
    else if (state == violationOfHighBoundary) { Serial.println("violationOfHighBoundary"); }
    else if (state == violationOfLowBoundary) { Serial.println("violationOfLowBoundary"); }
    else if (state == nonRelevant) { Serial.println("nonRelevant"); }
    else { Serial.println("Error"); }
  #endif

    // normal behaviour right
  if (state == withinBoundaries) {
    _right = value;

    // Normal behaviour left
  } else if (state == nonRelevant) {
    _left  = value;

    // right is overflowing
  } else if (state == countOverflow) {
    this->rightSetBottom();
    _left++;

    // right is underflowing
  } else if (state == countUnderflow) {
    this->rightSetTop(); // set to top legal value
    _left--;

  // NOTE: violationOfHighBoundary and violationOfLowBoundary reset
  //       right value to sit on the boundary
  } else if (state == violationOfHighBoundary) {
    this->rightSetTop(); // set to top legal value
  } else if (state == violationOfLowBoundary) {
    this->rightSetBottom(); // set to top legal value
  }

  #ifdef _DEBUG
    Serial.println("... ... ... Exiting function with ");
    Serial.print("... ... ... left: ");
    Serial.println(_left);
    Serial.print("... ... ... right: ");
    Serial.println(_right);
    Serial.println();
  #endif

  this->printToLedPanel();
  return state;
}
