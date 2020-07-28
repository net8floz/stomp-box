#include <memory>
#include "Arduino.h"
#include "SwitchController.h"

unsigned int SwitchController::get_currentState() const {
  return currentState;
}

boolean SwitchController::loop() {
  if ((millis() - lastDebounceTime) < debounceDelay) {
    return false;
  }

  currentState = digitalRead(DPIN);
  if (currentState == lastState) {
    return false;
  }
  lastState = currentState;
  lastDebounceTime = millis();
  return true;
}
