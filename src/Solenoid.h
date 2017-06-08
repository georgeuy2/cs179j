#ifndef Solenoid_h
#define Solenoid_h

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Solenoid {
  public:
  
    // Constructor
    Solenoid(byte sold_pin);
    
    // Datatypes
       
    // Methods
    void trigger();
    void on();
    void off();
    void setState(boolean decision);
    boolean getState();
    
  private:
    // Constructor
  
    // Datatypes
    byte sold_pin;
    boolean solenoidState;
    // Methods
  
};

#endif
