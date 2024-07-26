void setup() {
    // Initialize the serial communication at 9600 baud rate
    Serial.begin(9600);
}

void loop() {
    // Read the analog value from pin A1
    int sensorValue = analogRead(A1);

    // Convert the analog value to voltage
    // Assuming a 5V reference voltage and 10-bit ADC (0-1023)
    float voltage = sensorValue * (5.0 / 1023.0);

    // Print the voltage value to the Serial Monitor
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println(" V");

    // Wait for a second before the next reading
    delay(1000);
}