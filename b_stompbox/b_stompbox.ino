#include "StompSwitch.cpp"
#include "Light.h"
#include <memory>
#include "SwitchController.h"

const unsigned int SWITCH_left = 0;
const unsigned int SWITCH_center = 1;
const unsigned int SWITCH_right = 2;
const unsigned int SWITCH_side = 3;

const unsigned int LED_teensy =  13;
const unsigned int LED_power = 23;
const unsigned int LED_left = 22;
const unsigned int LED_center = 21;
const unsigned int LED_right = 20;

enum RunMode { Run, Configure };

RunMode runMode = Run;

std::vector<std::shared_ptr<Light>> lights;
std::vector<std::shared_ptr<StompSwitch>> stompSwitches;
std::shared_ptr<Light> powerLight;

SwitchController configSwitch(SWITCH_side);

const std::shared_ptr<Light> createLight(const unsigned int DPIN) {
  std::shared_ptr<Light> light = std::make_shared<Light>(DPIN);
  light->blink(10, 200);
  light->turnOff();
  lights.push_back(light);
  return light;
}

void setup() {
  // initialize the LED pin as an output:
  pinMode(LED_teensy, OUTPUT);
  pinMode(LED_power, OUTPUT);
  pinMode(LED_left, OUTPUT);
  pinMode(LED_center, OUTPUT);
  pinMode(LED_right, OUTPUT);

  pinMode(SWITCH_left, INPUT_PULLUP);
  pinMode(SWITCH_center, INPUT_PULLUP);
  pinMode(SWITCH_right, INPUT_PULLUP);
  pinMode(SWITCH_side, INPUT_PULLUP);

  Serial.begin(9600);

  digitalWrite(LED_teensy, HIGH);

  // create switch lights
  std::shared_ptr<Light> leftLight = createLight(LED_left);
  std::shared_ptr<Light> centerLight = createLight(LED_center);
  std::shared_ptr<Light> rightLight = createLight(LED_right);

  powerLight = createLight(LED_power);
  powerLight->turnOn();

  stompSwitches.push_back(std::make_shared<StompSwitch>(SWITCH_left, 2, 91, 127, lights[0]));
  stompSwitches.push_back(std::make_shared<StompSwitch>(SWITCH_center, 2, 90, 127, lights[1]));
  stompSwitches.push_back(std::make_shared<StompSwitch>(SWITCH_right, 2, 89, 127, lights[2]));

  for (auto &stomp : stompSwitches) {
    stomp->resumeLight();
  }
}

void toggleMode() {
  if (runMode == Run) {
    runMode = Configure;
    for (auto &light : lights) {
      light->clearCommands();
      light->turnOff();
    }
    // that's a long time right?
    powerLight->blink(999999, 200);
  } else {
    runMode = Run;
    for (auto &light : lights) {
      light->clearCommands();
      light->turnOff();
    }
    for (auto &stomp : stompSwitches) {
      stomp->resumeLight();
    }
    powerLight->turnOn();
  }
}


void loop() {
  for (auto &light : lights) {
    light->loop();
  }

  if (configSwitch.loop()) {
    toggleMode();
  }

  for (auto &stomp : stompSwitches) {
    if (stomp->loop()) {
      if (runMode == Run) {
        stomp->sendSignal();
      } else {
        stomp->changeInputType();
      }
    }
  }
}
