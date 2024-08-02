const int switchPin = 8;  // Use any available digital pin


void initMainSwitch() {
  pinMode(switchPin, INPUT);
}

bool isMainSwitchOn() {
  return digitalRead(switchPin) == HIGH;
}