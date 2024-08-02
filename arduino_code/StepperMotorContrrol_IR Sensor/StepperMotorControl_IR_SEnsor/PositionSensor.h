// PositionSensor.h

#ifndef POSITION_SENSOR_H
#define POSITION_SENSOR_H

#include <Arduino.h>

const int IN_A5 = A5; // analog input
const int reach = 200;

void initWaterLevelPositionSensor() {
  pinMode(IN_A5, INPUT);
  //Serial.begin(9600);
}

bool getWaterLevelSensorPos() {
  int WaterLevelSensorPos = analogRead(IN_A5);
  Serial.println("Readin is:");
  Serial.println(WaterLevelSensorPos);
  return WaterLevelSensorPos < reach;
}

#endif // POSITION_SENSOR_H