#include "TempSensorHeaders.h"
#include "WaterLevelSensorHeaders.h"
#include "PhotoSensor.h"
#include "WaterPump.h"
#include "PositionSensor.h"
#include "StepperMotor.h"
//#include "Uart_eeprom_settings.h"
// #include "SolarPositionRTC.h"

int delayTime = 500; 
double waterLevel; 
double temp; 
float sunLevel; 
//struct Settings settings; 

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  //SetSettingsFromEeprom(settings); 
  // InitRTCSolarPosition();
  sensors.begin(); // what is this? 
  initWaterLevelSensor(); // init water level sensor

  initWaterLevelPositionSensor();
  initStepperMotors();
  // initialize the serial port:
  Serial.begin(9600);


}

bool initWaterLevelSensorPositionStepper() {
  Serial.println("SENSORS - LOW - UP");
  Serial.println(getWaterLevelSensorPos("LOWER"));
  Serial.println(getWaterLevelSensorPos("UPPER"));
  if (getWaterLevelSensorPos("LOWER") and not getWaterLevelSensorPos("UPPER")) {
    Serial.println("MOVE UP");
    stepperMove("up", 1);
    return 0;
  }
  else if (not getWaterLevelSensorPos("LOWER") and getWaterLevelSensorPos("UPPER")){ 
    Serial.println("MOVE DOWN");
    stepperMove("down", 1);
    return 0;
  }

  else if (not getWaterLevelSensorPos("LOWER") and not getWaterLevelSensorPos("UPPER")) {
    Serial.println("We can move forward");
    return 1;
  }
}

void loop() {

    while (not initWaterLevelSensorPositionStepper()) {
    Serial.println("Init stepper motor");
    delay(1000);
    }

    // reaching the minimum water level
    while (getWaterLevel() == 0) {
      if (not getWaterLevelSensorPos("LOWER") and not getWaterLevel() == 1) {
          Serial.println("Water level is low");
          stepperMove("down", 1);
      }
      else {
        Serial.println("Water level is low, add more water. We reached the limit of the sensor position");
        break;
      }
      }

    // Start to add water
    Serial.println("Start to add water");
    delay(1000);


  /*
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
  
  if ((waterLevel > settings.waterLevelThreshold) || (temp > settings.tempTarget) || (sunLevel < settings.sunThreshold)) {
    switchPump(0);
  } else {
    switchPump(1);
  }

  delay(delayTime); 
  */
}