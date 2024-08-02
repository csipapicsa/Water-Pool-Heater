#include <Stepper.h>

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
  Serial.println("Down");
  digitalWrite(dir_pin, LOW);
  digitalWrite(step_pin, LOW);

  for(int i = 0; i < 50; i++) { 
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(step_pin, LOW);
    delay(8);
  }
  delay(50);
  digitalWrite(dir_pin, HIGH);

  Serial.println("UP");

  for(int i = 0; i < 200; i++) { 
    digitalWrite(step_pin, HIGH);
    delayMicroseconds(10);
    //delay(1000);
    digitalWrite(step_pin, LOW);
    delay(8);
    //delay(1000);
  }

  delay(20);

  // step one revolution in the other direction:
  
  delay(200);
}


