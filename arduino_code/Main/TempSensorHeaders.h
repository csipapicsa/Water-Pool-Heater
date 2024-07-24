#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS A4 // TODO TO BE CHECKED
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

double getWaterTemperature()
{
  sensors.requestTemperatures(); 
  return Serial.print(sensors.getTempCByIndex(0));
}