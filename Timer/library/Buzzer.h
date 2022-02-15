/*
 * Buzzer.h
 *
 * Manage Buzzer
 *
 * Author: berto.d.sera@gmail.com
 * 15.02.2022 - Version 1.0
 *
 */

#ifndef BUZZER_H
#define BUZZER_H

#include "Arduino.h"

class Buzzer {
    uint8_t _pin;
  public:
    Buzzer::Buzzer( uint8_t pin );

    Buzzer::init();

    Buzzer::tic();
};

#endif /* BUZZER_H */
