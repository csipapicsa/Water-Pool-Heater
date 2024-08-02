#include <Stepper.h>


// it should be in the global scope for some reasons
const int step_pin = 10;
const int dir_pin = 11;
const int power_pin_stepper = A4;  // New pin for power control

void stepperMove(String direction);

void initStepperMotors() {
  pinMode(step_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(power_pin_stepper, OUTPUT);  // Set A4 as output
  digitalWrite(power_pin_stepper, LOW);  // Initially set to LOW (motor off)
}

void stepperMove(String direction) {
  digitalWrite(power_pin_stepper, HIGH);
  if (direction == "down") {
    digitalWrite(dir_pin, LOW);
  }
  else if (direction == "up") {
    digitalWrite(dir_pin, HIGH);
  }
  else {
    digitalWrite(power_pin_stepper, LOW);
    return; // Invalid direction
  }

  for(int i = 0; i < 100; i++) { 
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(step_pin, LOW);
    delay(10);
  }

  digitalWrite(power_pin_stepper, LOW);
}