#define photoSensorInput A1

float getSolarvoltage();
int solarSensorValue;
float voltage;


float getSolarvoltage()
{
  solarSensorValue = analogRead(photoSensorInput);
  voltage = solarSensorValue * (5.0 / 1023.0);
  return voltage;
}