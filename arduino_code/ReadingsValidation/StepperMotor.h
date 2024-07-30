#include <Stepper.h>


// it should be in the global scope for some reasons
const int step_pin = 10;
const int dir_pin = 11;

void stepperMove(String direction);

void initStepperMotors() {
  pinMode(step_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
}

void stepperMove(String direction) {
  if (direction == "clockwise") {
    digitalWrite(dir_pin, LOW);
  }
  else if (direction == "counterclockwise") {
    digitalWrite(dir_pin, HIGH);
  }
  else {
    return; // Invalid direction
  }

  for(int i = 0; i < 100; i++) { 
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(20);
    digitalWrite(step_pin, LOW);
    delay(20);
  }
}