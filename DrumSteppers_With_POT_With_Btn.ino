#include <AccelStepper.h>
#include <limits.h>


// Define a stepper and the pins it will use
AccelStepper stepper1(AccelStepper::DRIVER, 9, 8); // step, dir
AccelStepper stepper2(AccelStepper::DRIVER, 13, 12); // step, dir

int pos = 0;
const int POT_PIN = A0;
int pot_val = 0;
int old_pot_val = 0;
int jitter = 20;
int max_steps = 3600; // default for Big Easy is 1/16 micro-steps
//                           (MS1, MS2, MS3 all high) 42BYGHM809 stepper motor is 400 full steps per rev.

int solenoidPin = 2;
int btnPin = 3;


void setup() {  

   Serial.begin(9600);
   
   pinMode(solenoidPin, OUTPUT); //Solenoid Start-up

   pinMode(btnPin, INPUT_PULLUP); //btn Pin

  
  stepper1.setMaxSpeed(8000);
  stepper1.setAcceleration(ULONG_MAX); // maxium accelleration
 
  pinMode(POT_PIN, INPUT);
  Serial.begin(9600);
 
  pot_val = analogRead(POT_PIN);
  pos = map(pot_val, 0, 1023, 0, max_steps);
  stepper1.setCurrentPosition(pos); // no movement at startup; assume pot and stepper are at the right position
  
  stepper2.setMaxSpeed(8000);
  stepper2.setAcceleration(ULONG_MAX); // maxium accelleration
 
  pinMode(POT_PIN, INPUT);
  Serial.begin(9600);
 
  pot_val = analogRead(POT_PIN);
  pos = map(pot_val, 0, 1023, 0, max_steps);
  stepper2.setCurrentPosition(pos); // no movement at startup; assume pot and stepper are at the right position
}

void loop() {
  if (digitalRead(btnPin) == LOW) {
    hit();
  }
  pot_val = analogRead(POT_PIN);
  if (abs(pot_val - old_pot_val) > jitter) {
    old_pot_val = pot_val;
    pos = map(pot_val, 0, 1023, 0, max_steps);
    Serial.print("pot = ");
    Serial.print(pot_val);
    Serial.print(" pos = ");
    Serial.println(pos);
    stepper1.moveTo(pos);
    stepper2.moveTo(pos);
  }
 
    stepper1.run();
    stepper2.run();
}

void hit() {
  digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
  delay(100);                      //Wait 1 Second
  digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
  delay(300);                      //Wait 1 Second
}

