
//StepperMotor.h
#include <Stepper.h>

enum StepDirection {
  StepDirection_Down, 
  StepDirection_Up,

  StepDirection_Count
};

const int step_pin = 10;
const int dir_pin = 11;

void stepperMove(StepDirection direction, float revolutions);
void initStepperMotors();


void initStepperMotors() {
  pinMode(step_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
}

void stepperMove(StepDirection direction, float revolutions) {
  switch(direction) {
    case StepDirection_Down:
      digitalWrite(dir_pin, LOW);
      break;
    case StepDirection_Up: 
      digitalWrite(dir_pin, HIGH);
      break;
    default: 
      break; // Invalid direction, should handle this case more proper like return -1 and caller should handle
  }

  int steps = 200 * revolutions;
  for(int i = 0; i <= steps; i++) { 
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(step_pin, LOW);
    delay(10);
  }
}