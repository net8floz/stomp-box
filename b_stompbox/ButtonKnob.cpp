//#include "Arduino.h"
//class ButtonKnob {
//  private:
//    volatile int value = 0;
//    volatile int lastValue = 0;
//    int PWPIN;
//    int DPIN;
//  public:
//    setup(const int PWPIN, const int DPIN) {
//      this->PWPIN = PWPIN;
//      this->DPIN = DPIN;
//
//      pinMode(PWPIN, INPUT);
//      pinMode(DPIN, INPUT);
//
//      digitalWrite(PWPIN, HIGH);
//      digitalWrite(DPIN, HIGH);
//    }
//
//    const int getValue() const {
//      return value;
//    }
//    const int getPWPIN() const {
//      return PWPIN;
//    }
//    const int getDPIN() const {
//      return DPIN;
//    }
//    const boolean onInterrupt() {
//      int MSB = digitalRead(DPIN); //MSB = most significant bit
//      int LSB = digitalRead(PWPIN); //LSB = least significant bit
//
//      int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
//      int sum = (lastValue << 2) | encoded; //adding it to the previous encoded value
//      if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) value++;
//      if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) value--;
//
//      if (lastValue == value) {
//        return false;
//      }
//
//      lastValue = value; //store this value for next time
//      Serial.print(value);
//      return true;
//    }
//};
//
