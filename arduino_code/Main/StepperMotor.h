
//StepperMotor.h
#include <Stepper.h>

enum StepDirection {
  StepDirection_Down, 
  StepDirection_Up,

  StepDirection_Count
};

const int step_pin = 10;
const int dir_pin = 11;
//const int power_pin_stepper = A4;

void stepperMove(StepDirection direction, int revolutions);
void initStepperMotors();


void initStepperMotors() {
  pinMode(step_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  //pinMode(power_pin_stepper, OUTPUT); 
  //digitalWrite(power_pin_stepper, LOW);
}

void stepperMove(StepDirection direction, int revolutions) {
  //digitalWrite(power_pin_stepper, HIGH);
  switch(direction) {
    case StepDirection_Down:
      digitalWrite(dir_pin, LOW);
      return; 
    case StepDirection_Up: 
      digitalWrite(dir_pin, HIGH);
      return; 
    default: 
      return; // Invalid direction, should handle this case more proper like return -1 and caller should handle
  }

  int steps = 200 * revolutions;
  for(int i = 0; i <= steps; i++) { 
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(step_pin, LOW);
    delay(10);
  }

  //digitalWrite(power_pin_stepper, LOW);
}