#include "TempSensorHeaders.h"
#include "WaterLevelSensorHeaders.h"
#include "PhotoSensor.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sensors.begin();
}

void loop() {
  Serial.println("------");
  Serial.println("Celsius temperature: ");
  Serial.println(getWaterTemperature());
  Serial.println("Get Water level");
  Serial.println(getWaterLevel());
  Serial.println("Get Photo Sensor Voltage");
  Serial.println(getSolarvoltage());


  delay(1000);
}
