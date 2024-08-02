# include "PhotoSensor.h"
# include "TempSensorHeaders.h"
# include "WaterPump.h"
# include "WaterLevelSensorHeaders.h"
# include "StepperMotor.h"
//#include "Uart_eeprom_settings.h"

# include "MainSwitch.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initWaterLevelSensor();
  initStepperMotors();
  initWaterPump();
  initMainSwitch();

}

void loop() {
  // put your main code here, to run repeatedly:
  if isMainSwitchOn() {
    Serial.println("Main Switch is on");
    Serial.println("-------------------");
    Serial.println("Get Photo Sensor");
    Serial.println(getSolarvoltage());
    Serial.println("Get Water Level Sensor - String: ");
    Serial.print(getWaterLevel());
    Serial.print(" / Get Water Level Sensor - Raw: ");
    Serial.println(getWaterLevelRaw());
    Serial.println("Get Temperature Sensor");
    Serial.println(getWaterTemperature());
    stepperMove("clockwise");
    delay(1000);
    stepperMove("counterclockwise");
    waterPumpOn(1000);
    waterPumpOff(1000);
  } else {
    Serial.println("Main Switch is off");
    delay(1000);
  }

  

}
