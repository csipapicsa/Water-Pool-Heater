#include "TempSensorHeaders.h"
#include "WaterLevelSensorHeaders.h"
#include "PhotoSensor.h"
#include "WaterPump.h"
#include "PositionSensor.h"
#include "StepperMotor.h"
#include "MainSwitch.h"
#include "Uart_eeprom_settings.h"

int delayTime = 1000; 
double waterLevel; 
double temp; 
float sunLevel; 
int waterLevelMin = 200; 
struct Settings settings; 
bool firstLoop; 

void updateSensorValues() {
  temp = getWaterTemperature();
  waterLevel = getWaterLevel();
  sunLevel = getSolarvoltage();
}

void printStatus() {
  Serial.print("Celsius temperature: ");
  Serial.print(temp);
  Serial.print(" (target ");
  Serial.print(settings.tempTarget);
  Serial.println(")");

  Serial.print("Water level: ");
  Serial.print(waterLevel);
  Serial.print(" (target ");
  Serial.print(settings.waterLevelThreshold);
  Serial.println(")");

  Serial.print("Photo Sensor Voltage: ");
  Serial.print(sunLevel);
  Serial.print(" (target ");
  Serial.print(settings.sunThreshold);
  Serial.println(")");

  Serial.println(); 
}

bool moveUpUntilOutOfWater() {
  bool upper = getWaterLevelSensorPos(SensorPosition_Upper); 

  if(upper) {
    Serial.println("CANNOT SET WATER LEVEL SENSOR HIGHER!");
    return 1;
  } else if(getWaterLevel() > waterLevelMin) {
    Serial.println("MOVE UP");
    stepperMove(StepDirection_Up, 1);
    return 0;
  }  else {
    Serial.print("Water level is out of water at: ");
    Serial.println(getWaterLevel());
    return 1; 
  }
}


void setup() {
  SetSettingsFromEeprom(settings); 
  initStepperMotors();
  initWaterLevelSensor(); // init water level sensor
  initMainSwitch();
  initWaterPump();
  sensors.begin(); // what is this? 
  // initialize the serial port:
  Serial.begin(9600);

/////////// move sensor up out of the water
initpause: 
  while(1) {
    delay(100);
    if(MainSwitchState() == 0) {
      goto initpause;
    }
    if(moveUpUntilOutOfWater() == 1) {
      Serial.println("MOVED SENSOR OUT OF WATER");
      break;
    }
  }
/////////// move sensor down just into the water
  while (getWaterLevel() < waterLevelMin) {
    if(MainSwitchState() == 0) {
      goto initpause;
    }
    if (!getWaterLevelSensorPos(SensorPosition_Lower)) {
      Serial.println("Water level is lower, so moving water level sensor down");
      stepperMove(StepDirection_Down, 1);
    } else {
      Serial.println("Water level is low, add more water. We reached the limit of the sensor position");
      break;
    }
    delay(300); 
  }
  Serial.println("MOVED SENSOR JUST INTO WATER");
}

void loop() {
  UpdateConfigFromSerial(settings); // checks for messages from user, and if received it will reset the settings.

  if(MainSwitchState() == 0) {
    switchPump(0);
    while(MainSwitchState() == 0) {
      delay(1000); // do nothing
      Serial.println("PAUSED");
      updateSensorValues();
      printStatus();
    }
  } 
    
  Serial.println("------");
  updateSensorValues();
  printStatus();

    
  if ((waterLevel > settings.waterLevelThreshold) || (temp > settings.tempTarget) || (sunLevel < settings.sunThreshold)) {
    Serial.println("Don't pump!");
    switchPump(0);
  } else {
    switchPump(1);
    Serial.println("Pump!");
  }

  delay(delayTime); 
}