// Main.ino

#include "PositionSensor.h"
#include "StepperMotor.h"

void setup() {
  initWaterLevelPositionSensor();
  initStepperMotors();
  // initialize the serial port:
  Serial.begin(9600);
}

bool initWaterLevelSensorPositionStepper() {

  Serial.print(getWaterLevelSensorPos("LOWER"));
  Serial.print(getWaterLevelSensorPos("UPPER"));
  if (getWaterLevelSensorPos("LOWER") and not getWaterLevelSensorPos("UPPER")) {
    Serial.println("MOVE UP");
    stepperMove("up", 1);
    return 0;
  }
  else if (not getWaterLevelSensorPos("LOWER") and getWaterLevelSensorPos("UPPER")){ 
    Serial.println("MOVE DOWN");
    stepperMove("down", 1);
    return 0;
  }

  else if (not getWaterLevelSensorPos("LOWER") and not getWaterLevelSensorPos("UPPER")) {
    Serial.println("We can move forward");
    return 1;
  }
}


void loop() {

  while (not initWaterLevelSensorPositionStepper()) {
    Serial.println("Init stepper motor")
    delay(1000);
  }

  
    
}


