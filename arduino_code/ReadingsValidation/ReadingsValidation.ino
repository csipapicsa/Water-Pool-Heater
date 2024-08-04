# include "PhotoSensor.h"
# include "TempSensorHeaders.h"
# include "WaterPump.h"
# include "WaterLevelSensorHeaders.h"
# include "StepperMotor.h"
# include "PositionSensor.h"
# include "MainSwitch.h"
//#include "Uart_eeprom_settings.h"

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
  if (MainSwitchState()) {
    Serial.println("************************");
    Serial.println("Main Switch is on");
    Serial.println("Get Photo Sensor");
    Serial.println(getSolarvoltage());
    Serial.println("Get Water Level Sensor - String: ");
    Serial.print(getWaterLevel());
    Serial.print(" / Get Water Level Sensor - Raw: ");
    Serial.println(getWaterLevelRaw());
    Serial.println("Get Temperature Sensor");
    Serial.println(getWaterTemperature());
    Serial.println("Get Upper Sensor RAW");
    Serial.println(getWaterLevelSensorPos(SensorPosition_Upper));
    Serial.println("Get Lower Sensor RAW");
    Serial.println(getWaterLevelSensorPos(SensorPosition_Lower));
    stepperMove(StepDirection_Down, 0.5);
    delay(1000);
    stepperMove(StepDirection_Up, 0.2);
    waterPumpOn(1000);
    waterPumpOff(1000);
  } else {
    Serial.println("Main Switch is off");
    delay(1000);
  }

  

}
