#include "MainSwitch.h"
#include "TempSensorHeaders.h"
#include "PhotoSensor.h"

float waterTempTarget = 27;
float PhotoThreshold = 2;

void setup() {
  initMainSwitch();
  initTempSensor();
  pinMode(A3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(MainSwitchState());
  Serial.println(getSolarvoltage());
  if (MainSwitchState()) {
    if (getWaterTemperature() < waterTempTarget and getSolarvoltage() > PhotoThreshold)
    {
      digitalWrite(A3, HIGH); // Turn the pin on
    }
    else if (getWaterTemperature() > waterTempTarget and getSolarvoltage() < PhotoThreshold) {
      digitalWrite(A3, LOW);
    }

    else if (getSolarvoltage() < PhotoThreshold) {
      digitalWrite(A3, LOW);
    }
    else if (getWaterTemperature() > waterTempTarget) {
      digitalWrite(A3, LOW);
    }
    
  } else {
    digitalWrite(A3, LOW);  // Turn the pin off
  }
  // delay(2500);
}