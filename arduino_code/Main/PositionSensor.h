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
  //Serial.begin(9600);
}

bool getWaterLevelSensorPos(SensorPosition pos) {
  // return 1 if sensing
  if (pos == SensorPosition_Upper) {
    int WaterLevelSensorPos = analogRead(IN_A4);
    //Serial.println("Readin is for UPPER:");
    //Serial.println(WaterLevelSensorPos);
    return WaterLevelSensorPos < reach_higher;
  } else if (pos == SensorPosition_Lower) {
    int WaterLevelSensorPos = analogRead(IN_A5);
    //Serial.println("Readin is for LOWER:");
    //Serial.println(WaterLevelSensorPos);
    return WaterLevelSensorPos < reach_lower;
  } else {
    // This should never happen actually
    return false;
  }
}

#endif // POSITION_SENSOR_H