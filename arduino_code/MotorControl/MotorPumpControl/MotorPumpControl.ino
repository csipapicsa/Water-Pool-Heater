#include "MainSwitch.h"
#include "TempSensorHeaders.h"

double waterTempTarget = 30;

void setup() {
  initMainSwitch();
  initTempSensor();
  pinMode(A3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(MainSwitchState());
  if (MainSwitchState()) {
    if (getWaterTemperature() < waterTempTarget)
    {
      digitalWrite(A3, HIGH); // Turn the pin on
    }
    else if (getWaterTemperature() > waterTempTarget) {
      digitalWrite(A3, LOW);
    }
    
  } else {
    digitalWrite(A3, LOW);  // Turn the pin off
  }
  delay(500);
}