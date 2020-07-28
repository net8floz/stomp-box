#pragma once
#include <memory>
#include "Arduino.h"

class SwitchController {
  private:
    unsigned int DPIN = 0;
    unsigned int currentState = LOW;
    unsigned int lastState = LOW;
    unsigned long lastDebounceTime = millis();
    unsigned long debounceDelay = 300;
    
  public:
    SwitchController(const unsigned int _DPIN){
      DPIN = _DPIN;
    }
    
    unsigned int get_currentState() const;
    
    boolean loop();
};
