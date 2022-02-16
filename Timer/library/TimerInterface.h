/*
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
    TimerInterface::TimerInterface();
    void TimerInterface::init();

    void TimerInterface::setBrightness(uint8_t value);

    // enum WhichButton { modeButton, sideButton, noButton};
    void TimerInterface::pollButtons ();


    // This function updates the display and returns information on potential
    //   further operations to be performed on the encoder object
    //   ref: FlowState { countOverflow, withinBoundaries, countUnderflow, violationOfHighBoundary, violationOfLowBoundary, nonRelevant };
    void TimerInterface::updateFromEncoder (uint8_t target, boolean rightSide);

    // enum FocusTarget { timerUI, sourceUI, targetUI, brightnessUI };
    void TimerInterface::focusEncoderOn (FocusTarget destination, boolean rightSide);
};

#endif /* TIMERINTERFACE_H */