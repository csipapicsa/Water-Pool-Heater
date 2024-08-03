#ifndef TEMPSENSORHEADERS_H
#define TEMPSENSORHEADERS_H

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
double watertemp;

// Function prototypes
void initTempSensor();
double getWaterTemperature();

void initTempSensor() {
  sensors.begin();
}

double getWaterTemperature() {
  sensors.requestTemperatures();
  watertemp = sensors.getTempCByIndex(0);
  Serial.println(watertemp);
  return watertemp;
}

#endif