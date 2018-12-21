#include <Servo.h>

// Joystick pin definitions
const int analogX = A0;
const int analogY = A1;

// Servo pin definitions
const int clawPin = 9;
const int basePin = 3;
const int backFrontFinePin = 11;
const int backFrontRoughPin = 10;

// dynamic values for joystick
int xval = 0;
int yval = 0;
int basePos = 0;
int armPos = 0;

// servos
Servo claw;
Servo base;
Servo backFrontFine;
Servo backFrontRough;

void setup() {

  // joystick pinmodes

  pinMode(analogX, INPUT);
  pinMode(analogY, INPUT);

  // servo pinmodes
  pinMode(clawPin, OUTPUT);
  pinMode(basePin, OUTPUT);
  pinMode(backFrontFinePin, OUTPUT);
  pinMode(backFrontRoughPin, OUTPUT);

  // serial
  Serial.begin(9600);

  // servo attachment to pins
  claw.attach(clawPin);
  base.attach(basePin);
  backFrontFine.attach(backFrontFinePin);
  backFrontRough.attach(backFrontRoughPin);

  // do some voodoo here
}

void loop() {

  // read input from joystick
  xval = analogRead(analogX);
  yval = analogRead(analogY);

  // base position is either 0, 90, or 180 degress based on x-coordinate of joystick
  if (xval <= 470) {
    basePos = 0;
  } else if (xval > 470 && xval < 530) {
    basePos = 90;
  } else if (xval >= 530) {
    basePos = 180;
  }

  // same with the backFrontRough servo, but with the y-coordinate insetad
  if (yval <= 470) {
    armPos = 0;
  } else if (yval > 470 && yval < 530) {
    armPos = 90;
  } else if (yval >= 530) {
    armPos = 180;
  }

  //  writing to servos
  base.write(basePos);
  backFrontRough.write(armPos);

  // debug prints
  Serial.println(xval);
  Serial.println(yval);

  // rate control
  delay(50);
}
