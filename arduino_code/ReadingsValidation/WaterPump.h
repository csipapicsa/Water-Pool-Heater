#define waterPumpSwitchPin A3

void initWaterPump();
void waterPumpOn(int duration);
void waterPumpOff(int duration);

void initWaterPump() {
    pinMode(waterPumpSwitchPin, OUTPUT);
}

void waterPumpOn(int duration) {
    if (duration > 1000) {
        return;
    }
    else {
        digitalWrite(A3, HIGH);
        delay(duration);
    }
}

void waterPumpOff(int duration) {
    if (duration > 1000) {
        return;
    }
    else {
        digitalWrite(A3, LOW);
        delay(duration);
    }
}