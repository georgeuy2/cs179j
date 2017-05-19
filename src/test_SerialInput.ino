const int ledPin = 11;
char val [10];
int index;
int a;
void setup()
{
// begin the serial communication
Serial.begin(9600);
pinMode(ledPin, OUTPUT);
 index = 0;
 a=0;
}

void loop()
{
  
// check if data has been sent from the computer
if (Serial.available()) {
 // read the most recent byte (which will be from 0 to 255)
  byte ch = Serial.read ();
  val[index++] = ch;
  val [index] = '\0';

  Serial.println(val);

  a = atoi(val);
  Serial.println(a);

 if (ch <= '0' || ch >= '9') {
   index = 0;
 }

// analogWrite(ledPin, var);
}
switch(a){
  case 0:
    Serial.println("Zero");
  break;

  case 1:
    Serial.println("One");
  break;

  case 2:
    Serial.println("Two");
  break;

  default:
     Serial.println("Nothing"); 
 }
}  
