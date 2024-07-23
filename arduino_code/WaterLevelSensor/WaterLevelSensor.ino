// Sensor pins
#define sensorPower 7
#define sensorPin A0

// Value for storing water level
int val = 0;
int lowerThreshold = 500;
int upperThreshold = 570;

void setup() {
	// Set D7 as an OUTPUT
	pinMode(sensorPower, OUTPUT);
	
	// Set to LOW so no power flows through the sensor
	digitalWrite(sensorPower, LOW);
	
	Serial.begin(9600);
}

void loop() {
	int level = readSensor();

	if (level == 0) {
		Serial.println("Water Level: Empty");
	}
	else if (level > 0 && level <= lowerThreshold) {
		Serial.println("Water Level: Low");
	}
	else if (level > lowerThreshold && level <= upperThreshold) {
		Serial.println("Water Level: Medium");
	}
	else if (level > upperThreshold) {
		Serial.println("Water Level: High");
	}
	delay(1000);
}
//This is a function used to get the reading
int readSensor() {
	digitalWrite(sensorPower, HIGH);	// Turn the sensor ON
	delay(10);							// wait 10 milliseconds
	val = analogRead(sensorPin);		// Read the analog value form sensor
	digitalWrite(sensorPower, LOW);		// Turn the sensor OFF
	return val;							// send current reading
}