#include "Arduino.h"
#include <vector>
#include <memory>
#include "Light.h"

boolean TurnOnCommand::loop() {
  digitalWrite(DPIN, HIGH);
  return true;
}

boolean TurnOffCommand::loop() {
  digitalWrite(DPIN, LOW);
  return true;
}

void BlinkCommand::toggleLight() {
  isOn = !isOn;
  digitalWrite(DPIN, isOn);
}

boolean BlinkCommand::loop() {

  if (!hasInit) {
    hasInit = true;
    currentTimestamp = millis();
    digitalWrite(DPIN, LOW);
  }

  if ((millis() - currentTimestamp) >= intervalMs) {
    currentIteration++;
    toggleLight();
    currentTimestamp = millis();
  }

  return currentIteration >= count * 2;
}

void Light::clearCommands(){
  commands.clear();
}

void Light::blink(const unsigned int count, const unsigned long intervalMs) {
  std::shared_ptr<LightCommand> cmd = std::make_shared<BlinkCommand>(DPIN, count, intervalMs);
  this->commands.push_back(cmd);
}

void Light::turnOn() {
  std::shared_ptr<LightCommand> cmd = std::make_shared<TurnOnCommand>(DPIN);
  this->commands.push_back(cmd);
}

void Light::turnOff() {
  std::shared_ptr<LightCommand> cmd = std::make_shared<TurnOffCommand>(DPIN);
  this->commands.push_back(cmd);
}

boolean Light::loop() {
  if (this->commands.size() > 0) {
    if (this->commands[0]->loop()) {
      this->commands.erase(this->commands.begin());
      Serial.println(this->commands.size());
    }
  }
  return true;
}
