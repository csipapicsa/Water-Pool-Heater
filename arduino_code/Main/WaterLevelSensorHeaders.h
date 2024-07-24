#ifndef WATER_LEVEL_SENSOR_HEADERS_H
#define WATER_LEVEL_SENSOR_HEADERS_H

#include <Arduino.h>

#define sensorPower 7
#define sensorPin A0

extern int val;
extern int lowerThreshold;
extern int upperThreshold;

void setupWaterLevelSensor();
double getWaterLevel();
int readSensor();

#endif // WATER_LEVEL_SENSOR_HEADERS_H