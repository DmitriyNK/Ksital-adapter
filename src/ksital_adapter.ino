// LED pin number
// 13 pin - user LED of Z-Uno board
#define LED_PIN 13
#define GUARD_ON_PIN 4
#define GUARD_OFF_PIN 3

// Last saved LED value
byte currentValue;
boolean isSetGuardPins;

ZUNO_SETUP_CHANNELS(ZUNO_SWITCH_BINARY(getter, setter));

// the setup routine runs once when you press reset:
void setup() {
  pinMode(LED_PIN, OUTPUT); // setup pin as output
  pinMode(GUARD_ON_PIN, OUTPUT);
  pinMode(GUARD_OFF_PIN, OUTPUT);
  clearGuardPins();
}
// the loop routine runs over and over again forever:
void loop() {
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
    digitalWrite (GUARD_ON_PIN, HIGH);
    digitalWrite (GUARD_OFF_PIN, LOW);
  } else {                         // if equals zero
    //digitalWrite(LED_PIN, LOW);   //turn the LED off by making the voltage LOW
    digitalWrite (GUARD_ON_PIN, LOW);
    digitalWrite (GUARD_OFF_PIN, HIGH);
  }
  // we'll save our value for the situation, when the controller will ask us about it
  currentValue = value;
  digitalWrite(LED_PIN, HIGH);
  isSetGuardPins = true; 
}

byte getter() {
  return currentValue;
}

void clearGuardPins() {
  digitalWrite (GUARD_ON_PIN, LOW);
  digitalWrite (GUARD_OFF_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  isSetGuardPins = false;
}

