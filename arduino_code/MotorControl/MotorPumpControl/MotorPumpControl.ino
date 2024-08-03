# include "MainSwitch.h"

void setup() {
  initMainSwitch();
  pinMode(A3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
    Serial.println(MainSwitchState());
    if (MainSwitchState())
    {
      digitalWrite(A3, HIGH); // Turn the pin on           // Wait for 1 second
    }
    else {
      digitalWrite(A3, LOW);  // Turn the pin off         // Wait for 1 second

    }

}
