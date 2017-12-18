
#include <AccelStepper.h>
#include <limits.h>


// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::DRIVER, 9, 8); // step, dir

int pos = 0;
const int POT_PIN = A0;
int pot_val = 0;
int old_pot_val = 0;
int jitter = 20;
int steps_per_rev = 6400; // default for Big Easy is 1/16 micro-steps (MS1, MS2, MS3 all high)
//                           42BYGHM809 stepper motor is 400 full steps per rev.

void setup()
{  
  stepper.setMaxSpeed(8000);
  stepper.setAcceleration(ULONG_MAX); // maxium accelleration
  
  pinMode(POT_PIN, INPUT);
  Serial.begin(9600);
  
  pot_val = analogRead(POT_PIN);
  pos = map(pot_val, 0, 1023, 0, steps_per_rev);
  stepper.setCurrentPosition(pos); // no movement at startup; assume pot and stepper are at the right position
}

void loop()
{
  pot_val = analogRead(POT_PIN);
  if (abs(pot_val - old_pot_val) > jitter) {
    old_pot_val = pot_val;
    pos = map(pot_val, 0, 1023, 0, 2*steps_per_rev);
    Serial.print("pot = ");
    Serial.print(pot_val);
    Serial.print(" pos = ");
    Serial.println(pos);
    stepper.runToNewPosition(pos); // blocking - waits until stepper reaches position
  }
  delay(1);
}
