#define waterPumpSwitchPin A3

void initWaterPump();
void switchPump(int status);

void initWaterPump() {
    pinMode(waterPumpSwitchPin, OUTPUT);
}

void switchPump(int status)
{
  if (status == 1) {
    digitalWrite(waterPumpSwitchPin, HIGH);
  }
  else if (status == 0)
  {
    digitalWrite(waterPumpSwitchPin, LOW);
  }
    
}