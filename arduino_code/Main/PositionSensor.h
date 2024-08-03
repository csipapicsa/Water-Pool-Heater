// PositionSensor.h

#ifndef POSITION_SENSOR_H
#define POSITION_SENSOR_H

#include <Arduino.h>

const int IN_A4 = A4; // UPPER
const int IN_A5 = A5; // LOWER
const int reach_lower = 200;
const int reach_higher = 500;

void initWaterLevelPositionSensor() {
  pinMode(IN_A5, INPUT);
  pinMode(IN_A4, INPUT);
  //Serial.begin(9600);
}

bool getWaterLevelSensorPos(String pos) {
  if (pos == "UPPER") {
    int WaterLevelSensorPos = analogRead(IN_A4);
    //Serial.println("Readin is for UPPER:");
    //Serial.println(WaterLevelSensorPos);
    return WaterLevelSensorPos < reach_higher;
  }
  else if (pos == "LOWER")
  {
    int WaterLevelSensorPos = analogRead(IN_A5);
    //Serial.println("Readin is for LOWER:");
    //Serial.println(WaterLevelSensorPos);
    return WaterLevelSensorPos < reach_lower;
  }

  

}

#endif // POSITION_SENSOR_H