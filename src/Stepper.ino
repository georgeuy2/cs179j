/*
#define but_pin 8
#define SOLENOID_PIN 22
#define step_pin 33 //35 37 39 41
#define en_pin 23 // 25 27 29 31
#define rot_pin 43 // 45 47 49 51


int index;
int counter = 0;
int MAX_LENGTH = 0;
boolean changeState = LOW;
boolean counterStart = LOW;
boolean state_solenoid = HIGH;



  //int cell[]={CELL_ONE, CELL_TWO, CELL_THREE, CELL_FOUR, CELL_FIVE, CELL_ZERO};
boolean receivedInput = false;
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

  pinMode(SOLENOID_PIN, OUTPUT);
  state_solenoid = HIGH;
  
  cellHasReached = LOW;
  counterStart = LOW;
  counter = 0;
  state = Start_State;
  input = 0;
  index = 0;
  getMaxLength();
  bCellInstance.bCell1 = false;
  bCellInstance.bCell2 = false;
  bCellInstance.bCell3 = false;
  bCellInstance.bCell4 = false;
  bCellInstance.bCell5 = false;
}



int ferrofluidDisplay(int state){
  
  switch(state){
    case Start_State:
   // Serial.println("@ Start State");
      if(!origin_State){
        sm1.goToOrigin();
      }
      else{
        state = Wait_State;
        input = 0; // make sure no user put any input before goign to wait state
      }
    break;

    case Wait_State:
      getSerial();
      if( input != 0){
       // Serial.println("@ Wait State");
        receivedInput = true;
        sendInput(input);
      }
      
        if(receivedInput == false){
         // Serial.println("@ 1 State");
          state = Wait_State;
        }
        else if(receivedInput && !movingStepper && origin_State){
         // Serial.println("@ 2 State");
        //Serial.println("@ Wait State");
          state = Move_State;
          sm1.setOriginState(false);
          movingStepper = true; // checks any of the motors states are moving
          counterStart = HIGH;
        }
    break;

    case Move_State:
  //  Serial.println(counter);
        if( receivedInput && movingStepper && !origin_State){
          state = Move_State;
         // counterStart = HIGH;
          sm1.goToCell(bCellInstance.bCell1, bCellInstance.bCell2, bCellInstance.bCell3, bCellInstance.bCell4, bCellInstance.bCell5);
          // if stepper finishes going to all cells then set receiveInputState = false 
        }
        else if( !receivedInput && !movingStepper && !origin_State){
          state = Start_State;
      //    Serial.println("Stop");
          sm1.setOriginState(false);
         // input = 0;
        }
    break;

    default:
      state = Start_State;
  }
  //Serial.println(state);

  return state;
}









int currentCell = 0;
boolean goHome = false;








  //int createLine(int currentCell){
  //  if( currentCell == 4 && cellHasReached == HIGH){
  //    currentCell = 5;
  //    cellHasReached = LOW;
  //    //turnOffSM();
  //    goHome = true;
  //  }
  //  else if( currentCell == 3 && cellHasReached == HIGH) {
  //    currentCell = 4;
  //    cellHasReached = LOW;
  //    pauseSM(5);
  //    counterStart = HIGH;
  //  }
  //    else if( currentCell == 2 && cellHasReached == HIGH) {
  //    currentCell = 3;
  //    cellHasReached = LOW;
  //    pauseSM(5);
  //    counterStart = HIGH;
  //  }
  //    else if( currentCell == 1 && cellHasReached == HIGH) {
  //    currentCell = 2;
  //    cellHasReached = LOW;
  //    pauseSM(5);
  //    counterStart = HIGH;
  //  }
  //    else if( currentCell == 0 && cellHasReached == HIGH) {
  //    currentCell = 1;
  //    cellHasReached = LOW; 
  //    pauseSM(5);
  //    counterStart = HIGH;
  //  }
  //  return currentCell;
  //}


void getMaxLength(){
  MAX_LENGTH = CELL_FOUR;
}
void loop() 
{

  //struct bCell bCellinstance;
  //  boolean one = bCellInstance.bCell1;
  //  boolean two = bCellInstance.bCell2;
  //  boolean three = bCellInstance.bCell3;
  //  boolean four = bCellInstance.bCell4;
  //  boolean five = bCellInstance.bCell5;

  
 state = ferrofluidDisplay(state);
  //getSerial();

  //if( input != NULL){
  //    //    Serial.println("@ Wait State");
  //       // receivedInput = true;
  //   //     Serial.print("\t");
  //        Serial.print(val);
  //        sendInput(val);
  //}
      
 
 //stepper(one, two, three, four, five);


}
 
*/
