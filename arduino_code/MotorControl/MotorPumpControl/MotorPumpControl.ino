void setup() {
  pinMode(A3, OUTPUT);
}

void loop() {
    digitalWrite(A3, HIGH); // Turn the pin on
    delay(500);            // Wait for 1 second
    digitalWrite(A3, LOW);  // Turn the pin off
    delay(500);            // Wait for 1 second
}
