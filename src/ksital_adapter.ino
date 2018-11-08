#include <RBD_Timer.h>

// define pins
#define PIN_LED 13          // 13 pin - user LED of Z-Uno board// 13 pin - user LED of Z-Uno board
#define PIN_GUARD_ON 4
#define PIN_GUARD_OFF 3
#define PIN_GUARD_STATUS 9

// Last saved LED value
byte currentValue;
byte lastStatus;
boolean isSetGuardPins;


//ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_BINARY(getter, setter),
//                    ZUNO_SENSOR_BINARY(ZUNO_SENSOR_BINARY_TYPE_GENERAL_PURPOSE, getterStatus));

ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_BINARY(getterStatus, setter));


// the setup routine runs once when you press reset:
void setup() {
  pinMode(PIN_LED, OUTPUT); // setup pin as output
  pinMode(PIN_GUARD_ON, OUTPUT);
  pinMode(PIN_GUARD_OFF, OUTPUT);
  pinMode(PIN_GUARD_STATUS, INPUT_PULLUP);
  clearGuardPins();
}
// the loop routine runs over and over again forever:
void loop() {
  byte currentStatus = digitalRead(PIN_GUARD_STATUS);
  if(currentStatus != lastStatus) {
    lastStatus = currentStatus;
    zunoSendReport(1);
  }
  if(isSetGuardPins) {
    delay(500);
    clearGuardPins();
  }

}
void setter(byte value) {
  // value is a variable, holding a "new value"
  // which came from the controller or other Z-Wave device
  if (value > 0) {               // if greater then zero
    //digitalWrite (LED_PIN, HIGH); //turn the LED on (HIGH is the voltage level)
    digitalWrite (PIN_GUARD_ON, HIGH);
    digitalWrite (PIN_GUARD_OFF, LOW);
  } else {                         // if equals zero
    //digitalWrite(LED_PIN, LOW);   //turn the LED off by making the voltage LOW
    digitalWrite (PIN_GUARD_ON, LOW);
    digitalWrite (PIN_GUARD_OFF, HIGH);
  }
  // we'll save our value for the situation, when the controller will ask us about it
  currentValue = value;
  digitalWrite(PIN_LED, HIGH);
  isSetGuardPins = true; 
}

byte getter() {
  return currentValue;
}

void clearGuardPins() {
  digitalWrite (PIN_GUARD_ON, LOW);
  digitalWrite (PIN_GUARD_OFF, LOW);
  digitalWrite(PIN_LED, LOW);
  isSetGuardPins = false;
}

byte getterStatus() {
  if (lastStatus == 0) { 
    return 0xff;              
  } else {                    
    return 0;                 
  }
}

