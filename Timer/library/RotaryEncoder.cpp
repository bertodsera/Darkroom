/*
 * RotaryEncoder.cpp
 *
 * Manage Rotary Encoder Object
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#include "Arduino.h"
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(uint8_t aPin, uint8_t bPin, int16_t minValue, int16_t maxValue, int16_t initialValue, uint8_t type = FULL_PULSE) :
  _encoder(aPin, bPin, minValue, maxValue, initialValue, type) {
  _value  = initialValue;
  _minVal = minValue;
  _maxVal = maxValue;
}

void RotaryEncoder::init () {
  NewEncoder::EncoderState state;
  Serial.println("Starting Encoder");

  if (!_encoder.begin()) {
    Serial.println("  Encoder Failed to Start. Check pin assignments and available interrupts. Aborting.");
    while (1) {
      yield();
    }
  } else {
    _encoder.getState(state);
    Serial.print("  Encoder Successfully Started at value = ");
    _value = state.currentValue;
    Serial.println(_value);
  };
}


boolean RotaryEncoder::pollValue () {
  NewEncoder::EncoderState currentEncoderState;

  if (_encoder.getState(currentEncoderState)) {
    if (currentEncoderState.currentValue != _value) {
      _value = currentEncoderState.currentValue;
      #ifdef _DEBUG
        Serial.println("... ... RotaryEncoder::pollValue");
        Serial.print("... ... ... value: ");
        Serial.println(_value);
        Serial.println();
      #endif
      return true;
    };
  };
  return false;
}

boolean RotaryEncoder::newSettings(int16_t newMin, int16_t newMax, int16_t newCurrent) {
  NewEncoder::EncoderState state;
  #ifdef _DEBUG
    Serial.println("... ... RotaryEncoder::newSettings");
    Serial.print("... ... ... newMin: ");
    Serial.println(newMin);
    Serial.print("... ... ... newMax: ");
    Serial.println(newMax);
    Serial.print("... ... ... newCurrent: ");
    Serial.println(newCurrent);
    Serial.println();
  #endif
  _encoder.newSettings(newMin, newMax, newCurrent, state);
  _value  = newCurrent;
  _minVal = newMin;
  _maxVal = newMax;
}

boolean RotaryEncoder::newValue(int16_t newCurrent) {
  NewEncoder::EncoderState state;
  #ifdef _DEBUG
    Serial.println("... ... RotaryEncoder::newValue");
    Serial.print("... ... ... newCurrent: ");
    Serial.println(newCurrent);
    Serial.println();
  #endif
  _encoder.newSettings(_minVal, _maxVal, newCurrent, state);
  _value  = newCurrent;
}

int16_t RotaryEncoder::getValue () { return _value; };
