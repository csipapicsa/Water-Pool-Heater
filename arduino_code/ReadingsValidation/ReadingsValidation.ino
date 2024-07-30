# include "PhotoSensor.h"
# include "TempSensorHeaders.h"
# include "WaterPump.h"
# include "WaterLevelSensorHeaders.h"
# include "StepperMotor.h"
//#include "Uart_eeprom_settings.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initWaterLevelSensor();
  initStepperMotors();

}

void loop() {
  // put your main code here, to run repeatedly:
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

}
