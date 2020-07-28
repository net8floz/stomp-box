#pragma once
#include "Arduino.h"
#include <vector>
#include <memory>
#include <string>

class LightCommand {
  protected:
    unsigned int DPIN = 0;
    std::string name = "";

  public:
    LightCommand(const unsigned int _DPIN) {
      DPIN = _DPIN;
    }

    std::string get_name() {
      return name;
    }
    
    virtual bool loop() = 0;
};

class TurnOnCommand : public LightCommand {
  public:
    TurnOnCommand(const unsigned int _DPIN) : LightCommand(_DPIN) { 
      name = "turnOn";  
    }

    boolean loop();
};

class TurnOffCommand : public LightCommand {
  public:
    TurnOffCommand(const unsigned int _DPIN) : LightCommand(_DPIN) {
      name = "turnOff";
    }

    boolean loop();
};

class BlinkCommand : public LightCommand {
  private:
    unsigned int count = 0;
    unsigned long intervalMs = 0;
    unsigned int currentIteration = 0;
    unsigned long currentTimestamp = 0;

    bool isOn = false;
    bool hasInit = false;

    void toggleLight();

  public:
    BlinkCommand(const unsigned int _DPIN, const unsigned int _count, const unsigned long _intervalMs ) : LightCommand(_DPIN) {
      count = _count;
      intervalMs = _intervalMs;
      name = "blink";
    }

    boolean loop();
};

class Light {
  private:
    unsigned int DPIN;
    std::vector<std::shared_ptr<LightCommand>> commands;

  public:

    Light(const unsigned int _DPIN){
      DPIN = _DPIN;
    }

    void clearCommands();

    void blink(const unsigned int count, const unsigned long intervalMs);

    void turnOn();

    void turnOff();

    boolean loop();
};
