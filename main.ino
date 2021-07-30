//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2036;
int stepsPerDegree = 6; // ~ 2036 / 360
char transmittedValue = 0;


int stepsToTake;
int speedM = 8; // Value between 1 and 12

// Creates 2 instances of a stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper base = Stepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper arm = Stepper(stepsPerRevolution, 4, 6, 5, 7);

void setup() {
  // Nothing to do (Stepper Library sets pins as outputs)
  Serial.begin(9600);
  base.setSpeed(speedM);
  arm.setSpeed(speedM);
}

void loop() {
  if (Serial.available() > 0) {
    transmittedValue = Serial.read();
    if (transmittedValue == 'r') {
        // Turn right (Clockwise) 90 degrees
        stepsToTake = 90 * stepsPerDegree;
        base.step(stepsToTake);
    }
    else if (transmittedValue == 'l') {
        // Turn left (Counter Clockwise) 90 degrees
        base.step(-stepsToTake);
    }
    else if (transmittedValue == 'u') {
        // Move Arm up (Counter Clockwise) 90 degrees
        arm.step(-stepsToTake);
    }
    else if (transmittedValue == 'd') {
        // Move Arm down (Clockwise) 90 degrees
        arm.step(stepsToTake);
    }
  }
}
