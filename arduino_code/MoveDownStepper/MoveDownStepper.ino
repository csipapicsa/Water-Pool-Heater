#include "StepperMotor.h"
#include "MainSwitch.h"
#include "PositionSensor.h"

void setup() {
  // put your setup code here, to run once:
  initMainSwitch();
  initStepperMotors();
  initWaterLevelPositionSensor();
  Serial.begin(9600);

}

void loop() {
  /*
  if (MainSwitchState()) {
    if (not (getWaterLevelSensorPos(SensorPosition_Lower)))
    {
    stepperMove(StepDirection_Down, 1);
    delay(200);
    Serial.println(getWaterLevelSensorPos(SensorPosition_Upper));
    Serial.println(getWaterLevelSensorPos(SensorPosition_Lower));
    }
    else {
      return;
    }
    }
  else {
    if (not (getWaterLevelSensorPos(SensorPosition_Upper)))
    {
    stepperMove(StepDirection_Up, 1);
    delay(200);
    Serial.println(getWaterLevelSensorPos(SensorPosition_Upper));
    Serial.println(getWaterLevelSensorPos(SensorPosition_Lower));
    }
    else {
      return;
    }
  }
  */
  if (MainSwitchState()) {
    stepperMove(StepDirection_Down, 1);
    Serial.println("***");
    Serial.println(getWaterLevelSensorPos(SensorPosition_Upper));
    Serial.println(getWaterLevelSensorPos(SensorPosition_Lower));
    Serial.println("***");
    delay(100);

  }
  else {
    delay(1000);
    Serial.println("***");
    Serial.println(getWaterLevelSensorPos(SensorPosition_Upper));
    Serial.println(getWaterLevelSensorPos(SensorPosition_Lower));
    Serial.println("***");
  }

}

