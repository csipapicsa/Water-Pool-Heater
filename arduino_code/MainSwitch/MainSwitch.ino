# include "MainSwitch.h"

void setup() {
  
  initMainSwitch();
  Serial.begin(9600);

}

void loop() {
    Serial.println(MainSwitchState());
    delay(1000);
}
