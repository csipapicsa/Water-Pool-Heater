#include <Arduino.h>

#define sensorPower 7
#define sensorPin A0

void setupWaterLevelSensor();
int getWaterLevel();
int readSensor();

int val = 0;
int emptyThreshold = 100;
int lowerThreshold = 350;
int upperThreshold = 570;

void initWaterLevelSensor() {
    pinMode(sensorPower, OUTPUT);
    digitalWrite(sensorPower, LOW);
}

int readSensor() {
    digitalWrite(sensorPower, HIGH);    // Turn the sensor ON
    delay(10);                          // Wait 10 milliseconds
    val = analogRead(sensorPin);        // Read the analog value from sensor
    digitalWrite(sensorPower, LOW);     // Turn the sensor OFF
    return val;                         // Send current reading
}

int getWaterLevel() {
    int level = readSensor();
    return level;  
}

int getWaterLevelRaw() {
    int level = readSensor();
    return level;
}