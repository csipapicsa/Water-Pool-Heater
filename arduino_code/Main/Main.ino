#include "TempSensorHeaders.h"
#include "WaterLevelSensorHeaders.h"
#include "PhotoSensor.h"
#include "WaterPump.h"
#include "Uart_eeprom_settings.h"
#include "SolarPositionRTC.h"

int delayTime = 500; 
double waterLevel; 
double temp; 
float sunLevel; 
struct Settings settings; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SetSettingsFromEeprom(settings); 
  InitRTCSolarPosition();
  sensors.begin(); // what is this? 
  initWaterLevelSensor(); // init water level sensor 
}

void loop() {
  UpdateConfigFromSerial(settings);
  
  Serial.println("------");
  Serial.println("Celsius temperature: ");
  temp = getWaterTemperature();
  Serial.println(temp);
  Serial.println("Get Water level");
  waterLevel = getWaterLevel();
  Serial.println(waterLevel);
  Serial.println("Get Photo Sensor Voltage");
  sunLevel = getSolarvoltage(); 
  Serial.println(sunLevel);
  
  if (waterLevel > settings.waterLevelThreshold) || (temp > settings.tempTarget) || (sunLevel > settings.sunThreshold) {
    switchPump(0);
  } else {
    switchPump(1);
  }

  delay(delayTime); 
}