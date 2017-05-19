#define but_pin 8
#define rot_pin 4
#define SOLENOID_PIN 13
#define en_pin 6
#define step_pin 5

int buttonState = 0;
boolean rotateState = LOW;
int index;
int counter = 0;
int MAX_LENGTH = 0;
boolean changeState = LOW;
boolean counterStart = LOW;
boolean cellHasReached = LOW;


const int WIDTH_NUM = 1000;
// Ideal range is about 1200-1300
const int CELL_FIVE = WIDTH_NUM;
const int CELL_FOUR = (CELL_FIVE/5)*4;
const int CELL_THREE = (CELL_FIVE/5)*3;
const int CELL_TWO = (CELL_FIVE/5)*2;
const int CELL_ONE = (CELL_FIVE/5);
const int CELL_ZERO = 0;

// Boolean Cells
boolean bCellOne;
boolean bCellTwo;
boolean bCellThree;
boolean bCellFour;
boolean bCellFive;

enum State{ Start_State, Wait_State, Move_State} state;
/*int Start_State = 0;
int Wait_State = 1;
int Move_State = 2;
int state = 0;
*/
int cell[]={CELL_ONE, CELL_TWO, CELL_THREE, CELL_FOUR, CELL_FIVE, CELL_ZERO};
boolean receivedInput = false;
boolean origin_State = false;
boolean movingStepper = false;

// Serial variable
char val[10];
int input; // 0 = no input, 1 = go to first cell,
           // 2 = go to second cell,..., 5 = go to fifth cell
           // 12 = go to first cell then second cell,
           // 123 = go to first to the third cell, and so on

struct boolCell{
  boolean bCell1;
  boolean bCell2;
  boolean bCell3;
  boolean bCell4;
  boolean bCell5;
};

struct boolCell bCellInstance;
// Setup
void setup() 
{
  Serial.begin(9600);
  pinMode(but_pin, INPUT);
  pinMode(en_pin, OUTPUT); //Enable
  pinMode(step_pin, OUTPUT); //Step
  pinMode(rot_pin, OUTPUT); //Direction
  pinMode(SOLENOID_PIN, OUTPUT);
  
  digitalWrite(rot_pin,HIGH);
  cellHasReached = LOW;
  counterStart = LOW;
  counter = 0;
  state = Start_State;
  input = 0;
  index = 0;
  getMaxLength();
  bCellInstance.bCell1 = true;
  bCellInstance.bCell2 = true;
  bCellInstance.bCell3 = true;
  bCellInstance.bCell4 = true;
  bCellInstance.bCell5 = true;
}

// get serial input
void getSerial(){
    if(Serial.available()){
      byte ch = Serial.read();
      val[index++] = ch;
      val[index] = '\0';

      input = atoi(val);

      if(ch<='0' || ch >= '9'){
        index=0;
      }
    }
}

int ferrofluidDisplay(int state){
  
  switch(state){
    case Start_State:
    Serial.println("@ Start State");
      if(!origin_State){
        goToOrigin();
      }
      else{
        state = Wait_State;
        input = 0; // make sure no user put any input before goign to wait state
      }
    break;

    case Wait_State:
      getSerial();
      if( input != 0){
        receivedInput = true;
      }
      Serial.println("@ Wait State");
        if(receivedInput == false){
          state = Wait_State;
        }
        else if(receivedInput && !movingStepper && origin_State){
          state = Move_State;
          origin_State = false;
        }
    break;

    case Move_State:
      Serial.println("@ Move State");
        if( receivedInput && movingStepper && !origin_State){
          state = Move_State; 
          
        }
        else if( !receivedInput && movingStepper && origin_State){
          state = Wait_State; 
        }
    break;

    default:
      state = Start_State;
  }
  //Serial.println(state);

  return state;
}

void goToOrigin(){
     if(buttonState == LOW){
        digitalWrite(rot_pin, HIGH);
        motorEn();
        motorRun();
        //counterStart = HIGH;
        //count = 0;
        
     } 
     else{
      motorOff();
      origin_State = true; 
     }
     //return origin_State;
}


int goToCell( int currentCell){
  
  if(counter > cell[currentCell]){
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
   // goToOrigin();
   }
    
    if(counterStart == HIGH ){
//      count++;
    }
return currentCell;
}

void pauseStepper(){
  motorOff();
  delay(800);
}

void stepper(boolean bCellOne, boolean bCellTwo, boolean bCellThree, boolean bCellFour, boolean bCellFive){
  // If any of the parameters are true it will go to that cell.
  // Starting from first cell to the last.
  //struct boolCell bCellInstance;
  //Serial.println(counterStart);

  if(counterStart == HIGH){
    counter++;
    digitalWrite(rot_pin,LOW);
    motorEn();
    motorRun();
  }
  
  if(bCellOne == false && bCellTwo == false &&  bCellThree == false && bCellFour == false && bCellFive == true){
    if(counter >= CELL_FIVE){
      bCellInstance.bCell5 = false;
      // trigger solenoid
      pauseStepper();
    }      
  }
  else if (bCellOne == false && bCellTwo == false &&  bCellThree == false && bCellFour == true  ){ //&& bCellFive == false
    if(counter >= CELL_FOUR){
      bCellInstance.bCell4 = false;
      pauseStepper();
      // trigger solenoid
    }  
  }
  else if (bCellOne == false && bCellTwo == false &&  bCellThree == true ){//&& bCellFour == false && bCellFive == false
    if(counter >= CELL_THREE){
      bCellInstance.bCell3 = false;
      // trigger solenoid
      pauseStepper();
    }    
  }
  else if(bCellOne == false && bCellTwo == true ){ //&&  bCellThree == false && bCellFour == false && bCellFive == false
    if(counter >= CELL_TWO){
      bCellInstance.bCell2 = false;
      // trigger solenoid
      pauseStepper();
    }
  }
  else if(bCellOne == true){ //&& bCellTwo == false &&  bCellThree == false && bCellFour == false && bCellFive == false
    if(counter >= CELL_ONE){
      bCellInstance.bCell1 = false;
      // trigger solenoid here
      pauseStepper();
    }
  }
  else if(bCellOne == false && bCellTwo == false &&  bCellThree == false && bCellFour == false && bCellFive == false){
    counterStart = LOW;
    motorOff();
    
  }
//  return bCellInstance;
}


int currentCell = 0;
boolean goHome = false;

void motorRun(){
  //motorEn();
  digitalWrite(step_pin,HIGH);
  delayMicroseconds(500);
  digitalWrite(step_pin,LOW);
  delayMicroseconds(500);
}
void motorEn(){
  digitalWrite(en_pin,LOW);
}

void motorOff(){
  digitalWrite(en_pin,HIGH);
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

void returnHome(){
  if(buttonState == LOW){
    digitalWrite(rot_pin,HIGH);
    motorEn();
    motorRun();
    
  }
  else{
   // motorOff();
    goHome = true;
  }
}
void getMaxLength(){
  MAX_LENGTH = CELL_FOUR;
}
void loop() 
{
//struct bCell bCellinstance;
  boolean one = bCellInstance.bCell1;
  boolean two = bCellInstance.bCell2;
  boolean three = bCellInstance.bCell3;
  boolean four = bCellInstance.bCell4;
  boolean five = bCellInstance.bCell5;

  buttonState = digitalRead(but_pin);
//  Serial.println(buttonState);
  if(buttonState == HIGH){
    counterStart = HIGH;
  }
  if(goHome == false){
    returnHome();
  }
  /*//goToOrigin(origin_State);
  state = ferrofluidDisplay(state);
*/
 
 stepper(one, two, three, four, five);

  

}
 

