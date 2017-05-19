#define but_pin 8
#define rot_pin 4
#define SOLENOID_PIN 13

boolean state_solenoid = HIGH;
int buttonState = 0;
boolean rotateState = LOW;
int index;
int count = 0;
boolean changeState = LOW;
boolean counterStart = LOW;
boolean cellHasReached = LOW;
int tempCell = 0;

const int CELL_FIVE = 1270;
const int CELL_FOUR = (CELL_FIVE/5)*4;
const int CELL_THREE = (CELL_FIVE/5)*3;
const int CELL_TWO = (CELL_FIVE/5)*2;
const int CELL_ONE = (CELL_FIVE/5);
const int CELL_ZERO = 0;
 
int cell[]={CELL_ONE, CELL_TWO, CELL_THREE, CELL_FOUR, CELL_FIVE, CELL_ZERO};
int currentCell = 0;
boolean goHome = false;
void setup() 
{
  Serial.begin(9600);
  pinMode(but_pin, INPUT);
  pinMode(6, OUTPUT); //Enable
  pinMode(5, OUTPUT); //Step
  pinMode(rot_pin, OUTPUT); //Direction
  pinMode(SOLENOID_PIN, OUTPUT);
  
  digitalWrite(rot_pin,HIGH);
  cellHasReached = LOW;
  tempCell = currentCell;

}

void solenoid(){
 for(index = 0; index < 2; index++){
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
}

void motorRun(){
  //motorEn();
  digitalWrite(5,HIGH);
  delayMicroseconds(500);
  digitalWrite(5,LOW);
  delayMicroseconds(500);
}
void motorEn(){
  digitalWrite(6,LOW);
}

void motorOff(){
  digitalWrite(6,HIGH);
}

void returnHome(){
  if(buttonState == LOW){
    digitalWrite(rot_pin,HIGH);
    motorEn();
    motorRun();
  }
  else{
    motorOff();
  }
}

void checkButtonIsPress(){
     if(buttonState == HIGH){
        digitalWrite(rot_pin,LOW);
        motorEn();
        motorRun();
        counterStart = HIGH;
        count = 0;
     }  
}

int goToCell( int currentCell){
  
  if(count > cell[currentCell]){
    cellHasReached = HIGH;
    counterStart = LOW;
    //digitalWrite(rot_pin,HIGH);
    
   // solenoid();    
    //count =0;
    //currentCell = 1;
    currentCell = createLine(currentCell);
   //motorEn();
   }

   if(currentCell != 5){
    checkButtonIsPress();
   }
    
    if(counterStart == HIGH ){
      count++;
    }
return currentCell;
}


void pauseMotor(int sec){
    sec = sec*100;  
    motorOff();
    delay(sec);
    motorEn();
}
int createLine(int currentCell){
  if( currentCell == 4 && cellHasReached == HIGH){
    currentCell = 5;
    cellHasReached = LOW;
    //motorOff();
    goHome = true;
  }
  else if( currentCell == 3 && cellHasReached == HIGH) {
    currentCell = 4;
    cellHasReached = LOW;
    pauseMotor(5);
    counterStart = HIGH;
  }
    else if( currentCell == 2 && cellHasReached == HIGH) {
    currentCell = 3;
    cellHasReached = LOW;
    pauseMotor(5);
    counterStart = HIGH;
  }
    else if( currentCell == 1 && cellHasReached == HIGH) {
    currentCell = 2;
    cellHasReached = LOW;
    pauseMotor(5);
    counterStart = HIGH;
  }
    else if( currentCell == 0 && cellHasReached == HIGH) {
    currentCell = 1;
    cellHasReached = LOW; 
    pauseMotor(5);
    counterStart = HIGH;
  }
  return currentCell;
}

void loop() 
{
  
  buttonState = digitalRead(but_pin);
  if(goHome == false){
    motorRun();
    currentCell = goToCell( currentCell );
  }
  else{
    returnHome();
  }
  //Serial.println(buttonState);
  
  


  

 }
  
 // displayState(); // this cause jitter to the stepper motor

\


