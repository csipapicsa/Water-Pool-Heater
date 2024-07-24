#include <Stepper.h>
/*
 Stepper Motor Control -  revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.

 */
//Stepper myStepper(stepsPerRevolution,10, 11);


const int step_pin = 10;
const int dir_pin = 11;

void setup() {
  pinMode(step_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step one revolution  in one direction:
  Serial.println("clockwise");
  digitalWrite(dir_pin, LOW);
  digitalWrite(step_pin, LOW);

  for(int i = 0; i < 100; i++) { 
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(step_pin, LOW);
    delay(10);
  }
  delay(200);
  digitalWrite(dir_pin, HIGH);

  for(int i = 0; i < 100; i++) { 
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(10);
    //delay(1000);
    digitalWrite(step_pin, LOW);
    delay(10);
    //delay(1000);
  }

  delay(200);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  delay(200);
}


