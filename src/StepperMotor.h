#ifndef StepperMotor_h
#define StepperMotor_h

#if (ARDUINO >= 100)
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define CW 0
#define CCW 1

#include "Solenoid.h"

class StepperMotor {
  public:
    // Constructor
    StepperMotor(byte step_pin, byte rot_pin, byte en_pin, byte sld_pin, byte but_pin, boolean dir = CCW);

    // Datatypes
    
    
    // Methods
    void pauseSM(int s);
    void turnOnSM();
    void turnOffSM();
    void runSM();
    void goToCells();
    void setDirection(boolean dir);
    void gotoOrigin();
    void setOriginState(boolean state);
    void setCells(boolean cellOne, boolean cellTwo, boolean cellThree, boolean cellFour, boolean cellFive);
    boolean isAtOrigin();
    boolean isMoving();
    //Solenoid solenoid;  
    
  private:
    // Data types
    const int WIDTH_NUM = 651;
    // Ideal range is about 1200-1300
    const int CELL_FIVE = WIDTH_NUM;
    const int CELL_FOUR = (CELL_FIVE/5)*4;
    const int CELL_THREE = (CELL_FIVE/5)*3;
    const int CELL_TWO = (CELL_FIVE/5)*2;
    const int CELL_ONE = (CELL_FIVE/5);
    const int CELL_ZERO = 0;
    const int MAX_COUNTER = 5000;
    byte step_pin;
    byte rot_pin;
    byte en_pin;
    byte but_pin;
    byte sold_pin;
    boolean dir;
    boolean buttonState;
    boolean originState;
    boolean moveState;
    boolean counterState;
    boolean bCellOne;
    boolean bCellTwo;
    boolean bCellThree;
    boolean bCellFour;
    boolean bCellFive;
    int seconds;
    int counter;
    unsigned long t1;
    unsigned long previousMillis;
    unsigned long t2;

    // Methods
    void startTimer();
    void resetCounter();
    void t1Start();
    void t2Start();
    void step();
    
};

#endif
