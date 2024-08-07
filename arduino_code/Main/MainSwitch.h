const int switchPin = 2;

void initMainSwitch() {
    pinMode(switchPin, INPUT_PULLUP);  // Enable internal pull-up resistor
}

bool MainSwitchState() {
    int switchState = digitalRead(switchPin);
  
    if (switchState == LOW) {
        return true;
    } else {
        return false;
    }
    
}