#include <Wire.h>

void initWaterLEvelPositionSensor() {
  bool getWaterLevelSensorPos();
  const int IN_A5 = A5; // analog input
  pinMode (IN_A5, INPUT);
  int WaterLevelSensorPos;
  const int reach = 500;
}


bool getWaterLevelSensorPos() {
  WaterLevelSensorPos = analogRead(IN_A5);
  if (WaterLevelSensorPos < reach) {
    return true;
  }
  else {
    return false;
  }
}