// Main.ino

#include "PositionSensor.h"
#include "StepperMotor.h"

void setup() {
  initWaterLevelPositionSensor();
  initStepperMotors();
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  if (getWaterLevelSensorPos()) {
    //stepperMove("up");
    //stepperMove("up");
    //stepperMove("up");
    //stepperMove("up");
    //stepperMove("up");
    //stepperMove("up");
  }
  else {
    stepperMove("down");
  }
  delay(1000);
}


