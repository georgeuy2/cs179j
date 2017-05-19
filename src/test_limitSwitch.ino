int led = 7;
int BUTTON_PIN = 8;
int buttonState =0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(BUTTON_PIN,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(BUTTON_PIN);
  Serial.println(buttonState);

  if(buttonState == HIGH){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
}
