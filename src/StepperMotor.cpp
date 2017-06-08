#include "StepperMotor.h"
#include "Solenoid.h"

StepperMotor::StepperMotor(byte s_pin, byte r_pin, byte e_pin, byte sld_pin, byte b_pin, boolean d = CCW){
  step_pin = s_pin;
  rot_pin = r_pin;
  en_pin = e_pin;
  but_pin = b_pin;
  sold_pin = sld_pin;
  counter = 0;
  originState = false;
  moveState = false;
  buttonState = false;
  counterState = false;
  setDirection(d);
  
  pinMode(step_pin, OUTPUT);
  pinMode(rot_pin, OUTPUT);
  pinMode(en_pin, OUTPUT);
  pinMode(but_pin, OUTPUT);
 
}

void StepperMotor::resetCounter(){
  counter = 0;
}

void StepperMotor::setCells(boolean cellOne, boolean cellTwo, boolean cellThree, boolean cellFour, boolean cellFive){
  bCellOne = cellOne;
  bCellTwo = cellTwo;
  bCellThree = cellThree;
  bCellFour = cellFour;
  bCellFive = cellFive;
  counterState = true;
}

void StepperMotor::goToCells(){
  // If any of the parameters are true it will go to that cell.
  // Starting from first cell to the last.
  //struct boolCell bCellInstance;

  
  if(counterState == true){
    // avoid overflow
    if(counter < MAX_COUNTER){
      counter++;
    }
    setDirection(CW);
    turnOnSM();
    runSM();
    setOriginState(false);
  }
  
  if(bCellOne == false && bCellTwo == false &&  bCellThree == false && bCellFour == false && bCellFive == false){
    counterState = false;
    resetCounter();
    turnOffSM();

  }
  else if(bCellOne == false && bCellTwo == false &&  bCellThree == false && bCellFour == false && bCellFive == true){
    if(counter >= CELL_FIVE){
      bCellFive = false;
      // trigger solenoid
      //solenoid.trigger();
      pauseSM(5);
    }      
  }
  else if (bCellOne == false && bCellTwo == false &&  bCellThree == false && bCellFour == true  ){ //&& bCellFive == false
    if(counter >= CELL_FOUR){
      bCellFour = false;
      pauseSM(5);
      // trigger solenoid
    }  
  }
  else if (bCellOne == false && bCellTwo == false &&  bCellThree == true ){//&& bCellFour == false && bCellFive == false
    if(counter >= CELL_THREE){
      bCellThree = false;
      // trigger solenoid
      pauseSM(5);
    }    
  }
  else if(bCellOne == false && bCellTwo == true ){ //&&  bCellThree == false && bCellFour == false && bCellFive == false
    if(counter >= CELL_TWO){
      bCellTwo = false;
      // trigger solenoid
      pauseSM(5);
    }
  }
  else if(bCellOne == true){ //
    if(counter >= CELL_ONE){
      bCellOne = false;
      //triggerSolenoid();
      
      pauseSM(5);
    }
  }

}


void StepperMotor::gotoOrigin(){
  buttonState = digitalRead(but_pin);
   
   if(buttonState == LOW){
      setDirection(CCW);
      turnOnSM();
      runSM();
      setOriginState(false);
      if(counter < MAX_COUNTER){
        counter++;
      }
   } 
   else{
    turnOffSM();
    setDirection(CW);
    setOriginState(true); 
    Serial.println(counter);
    resetCounter();
   }
}

boolean StepperMotor::isAtOrigin(){
  return originState;
}

boolean StepperMotor::isMoving(){
  return moveState;
}

void StepperMotor::setOriginState(boolean state){
  originState = state;
}



void StepperMotor::pauseSM(int sec){
    sec = sec*100;  
    turnOffSM();
    delay(sec);
    turnOnSM();
}

void StepperMotor::setDirection(boolean dir){
  if(dir == CW){
    digitalWrite(rot_pin, LOW);
  }
  else if(dir == CCW){
    digitalWrite(rot_pin, HIGH);
  }
}

void StepperMotor::runSM(){
  turnOnSM();
  unsigned long currentMillis = millis();
  if( currentMillis - previousMillis > 2){
    step();
    previousMillis = currentMillis;
  }
  
}
/*
 * fix the delay stepper and delay part to millis
 * 
 */
void StepperMotor::step(){
  static int lastStep = 0;
  switch(lastStep){
    case 0:
      digitalWrite(step_pin,HIGH);
      break;

    case 1:
      digitalWrite(step_pin,LOW);
      break;
  }
  lastStep++;
  if(lastStep > 2){
    lastStep = 0;
  }
}

void delaySM(unsigned long t){
  if(millis > t +3){
    
  }
}
void StepperMotor::t1Start(){
  t1 = millis();
}

void StepperMotor::t2Start(){
  t2 = millis();
}

void StepperMotor::turnOnSM(){
  digitalWrite(en_pin,LOW);
  moveState = true;
}

void StepperMotor::turnOffSM(){
  digitalWrite(en_pin,HIGH);
  moveState = false;
}

