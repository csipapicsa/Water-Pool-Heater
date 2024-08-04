#include "TempSensorHeaders.h"
#include "WaterLevelSensorHeaders.h"
#include "PhotoSensor.h"
#include "WaterPump.h"
#include "PositionSensor.h"
#include "StepperMotor.h"
#include "MainSwitch.h"
#include "Uart_eeprom_settings.h"
// #include "SolarPositionRTC.h"

int delayTime = 1000; 
double waterLevel; 
double temp; 
float sunLevel; 
int newSwitchState, oldSwitchState; 
int waterLevelMin = 100; 
struct Settings settings; 

bool moveUpUntilOutOfWater() {
  /*
    Moves the waterlevel sensor up 
   */
  // bool lower = getWaterLevelSensorPos(SensorPosition_Lower); 
  bool upper = getWaterLevelSensorPos(SensorPosition_Upper); 

  if (!upper && getWaterLevel() < waterLevelMin) {
    Serial.println("MOVE UP");
    stepperMove(StepDirection_Up, 1);
    return 0;
  }  else {
    return 1; 
  }
}


void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);
  // InitRTCSolarPosition();

  oldSwitchState = MainSwitchState();
  newSwitchState = MainSwitchState();

  SetSettingsFromEeprom(settings); 

  initStepperMotors();
  initWaterLevelSensor(); // init water level sensor
  initMainSwitch();
  initWaterPump();

  initWaterLevelSensorPosition(); 

  sensors.begin(); // what is this? 
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  UpdateConfigFromSerial(settings); // checks for messages from user, and if received it will reset the settings.

  newSwitchState = MainSwitchState();
  if(newSwitchState == 0) {
pause:
    switchPump(0);
    while(newSwitchState == 0) {
      delay(1000); // do nothing
      newSwitchState = MainSwitchState();
    }
    // when this point is reached it has changed from 0 to 1, meaning we should reposition and set the switchstate to 1
    
    while(1) {
      newSwitchState = MainSwitchState();
      if(newSwitchState == 0) 
        goto pause;
      if(moveUpUntilOutOfWater() == 1) {
        break;
      }
    }
    while (getWaterLevel() > waterLevelMin) {
      newSwitchState = MainSwitchState();
      if(newSwitchState == 0) 
        goto pause;
      if (!getWaterLevelSensorPos(SensorPosition_Lower)) {
          Serial.println("Water level is lower, so moving water level sensor down");
          stepperMove(StepDirection_Down, 1);
      } else {
        Serial.println("Water level is low, add more water. We reached the limit of the sensor position");
        break;
      }
      delay(300); 
    }

    oldSwitchState = newSwitchState;
  } 

  
  Serial.println("------");
  Serial.print("Celsius temperature: ");
  temp = getWaterTemperature();
  Serial.print(temp);
  Serial.print("\n Target temp: ");
  Serial.print(settings.tempTarget);
  Serial.print("\nGet Water level");
  waterLevel = getWaterLevel();
  Serial.print(waterLevel);
  Serial.print("\nTarget water level: ");
  Serial.print(settings.waterLevelThreshold);
  Serial.print("\nGet Photo Sensor Voltage");
  sunLevel = getSolarvoltage(); 
  Serial.print(sunLevel);
  Serial.print("\nTarget sun threshold: ");
  Serial.print(settings.sunThreshold); 
  Serial.println("\n");

  
  if ((waterLevel > settings.waterLevelThreshold) || (temp > settings.tempTarget) || (sunLevel < settings.sunThreshold)) {
    Serial.println("Don't pump!");
    switchPump(0);
  } else {
    switchPump(1);
    Serial.println("Pump!");
  }

  delay(delayTime); 
}