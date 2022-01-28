//
// Created by Alex Coulcher.
//

#ifndef B3LL_LOG_H
#define B3LL_LOG_H

#include <Arduino.h>


class Bell {
private:
  uint8_t outputPin;

public:
  Bell(uint8_t outputPin) {
    this->outputPin = outputPin;
    pinMode(outputPin, OUTPUT);
  }

  void ding() {
    digitalWrite(this->outputPin, LOW);
    delay(50);
    digitalWrite(this->outputPin, HIGH);
    delay(1000);
  }
};

#endif //B3LL_LOG_H