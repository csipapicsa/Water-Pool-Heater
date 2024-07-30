#include <Arduino.h>

#define sensorPower 7
#define sensorPin A0

void setupWaterLevelSensor();
double getWaterLevel();
int readWLSensor();

int val = 0;
int lowerThreshold = 500;
int upperThreshold = 570;

void initWaterLevelSensor() {
    pinMode(sensorPower, OUTPUT);
    digitalWrite(sensorPower, LOW);
}

int readWLSensor() {
    digitalWrite(sensorPower, HIGH);    // Turn the sensor ON
    delay(10);                          // Wait 10 milliseconds
    val = analogRead(sensorPin);        // Read the analog value from sensor
    digitalWrite(sensorPower, LOW);     // Turn the sensor OFF
    return val;                         // Send current reading
}

double getWaterLevel() {
    int level = readWLSensor();

    if (level == 0) {
        Serial.println("Water Level: Empty");
        return 0;
    } else if (level > 0 && level <= lowerThreshold) {
        Serial.println("Water Level: Low");
        return 1;
    } else if (level > lowerThreshold && level <= upperThreshold) {
        Serial.println("Water Level: Medium");
        return 2;
    } else if (level > upperThreshold) {
        Serial.println("Water Level: High");
        return 3;
    }
    return -1; // In case none of the above conditions are met
}

int getWaterLevelRaw() {
    int level = readWLSensor();
    return level;
}