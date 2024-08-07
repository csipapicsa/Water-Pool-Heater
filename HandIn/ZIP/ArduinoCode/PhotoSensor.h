#define photoSensorInput A1

float getSolarvoltage();

float getSolarvoltage()
{
  int solarSensorValue = analogRead(photoSensorInput);
  float voltage = solarSensorValue * (5.0 / 1023.0);
  return voltage;
}