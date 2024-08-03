 // The pin your switch is connected to

void initMainSwitch() {
    pinMode(switchPin, INPUT_PULLUP);  // Enable internal pull-up resistor
}

void setup() {

  const int switchPin = 2;
  initMainSwitch();
  Serial.begin(9600);
ű
}

bool MainSwitchStates() {
    int switchState = digitalRead(switchPin);
  
    if (switchState == LOW) {
        Serial.println("Switch is pressed");
    } else {
        Serial.println("Switch is not pressed");
    }
    
}

void loopt() {
    MainSwitchStates();
    delay(1000);
}