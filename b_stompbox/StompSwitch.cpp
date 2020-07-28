#include <memory>
#include "Arduino.h"
#include "Light.h"
#include "SwitchController.h"

class StompSwitch {
  private:
    enum InputType { ToggleStomp, OnOffStomp, OnStomp };
    unsigned int midiChannel;
    unsigned int midiController;
    int midiValue;

    std::shared_ptr<Light> light;
    std::shared_ptr<SwitchController> switchController;

    InputType inputType = ToggleStomp;

  public:
    StompSwitch(unsigned const int _DPIN, unsigned const int _midiChannel, unsigned const int _midiController, unsigned const int _midiValue, const std::shared_ptr<Light> _light) {
      switchController = std::make_shared<SwitchController>(_DPIN);
      light = _light;
      midiChannel = _midiChannel;
      midiController = _midiController;
      midiValue = _midiValue;
    }

    void changeInputType() {
      light->clearCommands();
      switch (inputType) {
        case OnOffStomp:
          inputType = OnStomp;
          light->blink(6, 100);
          break;
        case ToggleStomp:
          inputType = OnOffStomp;
          light->blink(2, 1000);
          break;
        case OnStomp:
          inputType = ToggleStomp;
          light->blink(1, 300);
          break;
      }
      light->turnOff();
    }

    void sendSignal() {
      switch (inputType) {
        case OnOffStomp:
          usbMIDI.sendControlChange(midiController, 127, midiChannel);
          usbMIDI.sendControlChange(midiController, 0, midiChannel);
          light->blink(6, 100);
          break;
        case ToggleStomp:
          usbMIDI.sendControlChange(midiController, switchController->get_currentState() * 127, midiChannel);
          if (switchController->get_currentState() == HIGH) {
            light->turnOn();
          } else {
            light->turnOff();
          }
          break;
        case OnStomp:
          usbMIDI.sendControlChange(midiController, 127, midiChannel);
          light->blink(1, 100);
          break;
      }
    }

    void resumeLight() {
      switch (inputType) {
        case OnOffStomp:
          light->turnOff();
          break;
        case ToggleStomp:
          if (switchController->get_currentState() == HIGH) {
            light->turnOn();
          } else {
            light->turnOff();
          }
          break;
        case OnStomp:
          light->turnOff();
          break;
      }
    }

    boolean loop() {
      return switchController->loop();
    }
};
