#define SOLENOID_PIN 13

boolean state_solenoid = HIGH;
void setup() {
  // put your setup code here, to run once:
  pinMode(SOLENOID_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(state_solenoid == HIGH){
      digitalWrite(SOLENOID_PIN, HIGH);
      state_solenoid = LOW;
  }
  else{
      digitalWrite(SOLENOID_PIN, LOW);
      state_solenoid = HIGH;
  }
  delay(100);
}
