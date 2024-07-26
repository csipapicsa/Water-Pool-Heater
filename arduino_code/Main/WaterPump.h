#define waterPumpSwitchPin A3

void setupWaterPump();
void switchPump(int status);

void setupWaterPump() {
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