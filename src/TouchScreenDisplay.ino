/*

#include <Nextion.h>

NexButton b0 = NexButton(0, 1, "b0");

NexTouch *nex_listen_list[] = 
{
  &b0,
  NULL
};

void buttonPress( void *ptr ){
  dbSerialPrintln("b0 Pressed");
}

void setup(void){
  nexInit();
  // If changed to any other baud make sure to change it according in the Serial monitor. 
  // ocated bottom right corner.
  Serial.begin(9600); 

  b0.attachPush(buttonPress);

  dbSerialPrintln("Setup Done");
}

void loop(void){
  nexLoop(nex_listen_list);
}
*/
