#include "TempSensorHeaders.h"
#include "WaterLevelSensorHeaders.h"
#include "PhotoSensor.h"
#include "WaterPump.h"
#include "PositionSensor.h"
#include "StepperMotor.h"
#include "MainSwitch.h"
#include "Uart_eeprom_settings.h"
// #include "SolarPositionRTC.h"

int delayTime = 500; 
double waterLevel; 
double temp; 
float sunLevel; 
int switchState; 
struct Settings settings; 

bool moveAwayFromBorder() {
  /*
    Moves the waterlevel sensor up or down from the border regions
   */
  Serial.println("SENSORS - LOW - UP");
  Serial.println(getWaterLevelSensorPos(SensorPosition_Lower));
  Serial.println(getWaterLevelSensorPos(SensorPosition_Upper));

  bool lower = getWaterLevelSensorPos(SensorPosition_Lower); 
  bool upper = getWaterLevelSensorPos(SensorPosition_Upper); 

  if (lower && !upper) {
    Serial.println("MOVE UP");
    stepperMove(StepDirection_Up, 1);
    return 0;
  } else if (!lower && upper) {
    Serial.println("MOVE DOWN");
    stepperMove(StepDirection_Down, 1);
    return 0;
  } else if (!lower && !upper) {
    return 1; 
  } else {
    Serial.println("This should never happen! Both IR sensors sense something");
    return 0; 
  }
}

void moveWaterLevelSensorDownToWater() {
  while (getWaterLevel() == 0) {
    if (!getWaterLevelSensorPos(SensorPosition_Lower)) {
        Serial.println("Water level is lower, so moving water level sensor down");
        stepperMove(StepDirection_Down, 1);
    } else {
      Serial.println("Water level is low, add more water. We reached the limit of the sensor position");
      break;
    }
    delay(300); 
  }
}

void initWaterLevelSensorPosition() {
  while(1) {
    if(moveAwayFromBorder() == 1) {
      break;
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);
  // InitRTCSolarPosition();

  switchState = MainSwitchState();

  SetSettingsFromEeprom(settings); 

  initWaterLevelPositionSensor();
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
  if(switchState == 0) {
    int newState = MainSwitchState();
    while(newState == 0) {
      delay(1000); // do nothing
      newState = MainSwitchState();
    }
    // when this point is reached it has changed from 0 to 1, meaning we should reposition and set the switchstate to 1
    
    // place the waterlevel holder where it ought to be, so if it is in border regions move it into middle
    initWaterLevelSensorPosition();
    moveWaterLevelSensorDownToWater();
    // reaching the minimum water level
    switchState == newState; 
  } 

  UpdateConfigFromSerial(settings); // checks for messages from user, and if received it will reset the settings.
  
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
  
  if ((waterLevel > settings.waterLevelThreshold) || (temp > settings.tempTarget) || (sunLevel < settings.sunThreshold)) {
    switchPump(0);
  } else {
    switchPump(1);
  }

  delay(delayTime); 
}