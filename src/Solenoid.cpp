#include "Solenoid.h"

Solenoid::Solenoid(byte s_pin){
  sold_pin = s_pin;
  solenoidState = false;
  pinMode(sold_pin, OUTPUT);
}

void Solenoid::trigger(){
   for( int i =0; i <2; i++){
     if(getState() == true){
         on();
         setState(false);
     }
     else{
         off();
         setState(true);     
     }
      delay(100);
   } 
}

void Solenoid::on(){
  digitalWrite(sold_pin, HIGH);
}

void Solenoid::off(){
  digitalWrite(sold_pin, LOW);
}

boolean Solenoid::getState(){
  return solenoidState;
}

void Solenoid::setState(boolean decision){
  solenoidState = decision;
}

