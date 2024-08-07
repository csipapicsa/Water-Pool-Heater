// PositionSensor.h

#ifndef POSITION_SENSOR_H
#define POSITION_SENSOR_H

#include <Arduino.h>

enum SensorPosition {
  SensorPosition_Upper,
  SensorPosition_Lower,

  SensorPosition_Count
};

const int IN_A4 = A4; // UPPER
const int IN_A5 = A5; // LOWER
const int reach_lower = 200;
const int reach_higher = 500;

void initWaterLevelPositionSensor() {
  pinMode(IN_A5, INPUT);
  pinMode(IN_A4, INPUT);
}

bool getWaterLevelSensorPos(SensorPosition pos) {
  // return 1 if sensing
  if (pos == SensorPosition_Upper) {
    int WaterLevelSensorPos = analogRead(IN_A4);
    return WaterLevelSensorPos < reach_higher;
  } else if (pos == SensorPosition_Lower) {
    int WaterLevelSensorPos = analogRead(IN_A5);
    return WaterLevelSensorPos < reach_lower;
  } else {
    return false;
  }
}

#endif // POSITION_SENSOR_H