int SOL_PIN=2; //Solenoid control circuit
  
void setup() {
  pinMode(SOL_PIN, OUTPUT);
}

void loop() {
  digitalWrite(SOL_PIN, HIGH);
  delay(300);
  digitalWrite(SOL_PIN, LOW); 
  delay(1000);
}
