#include <Wire.h>


#define INTERRUPT 2
#define PIN_M_DLEN 3
#define PIN_S_DLEN 4
#define CLOCK 5
#define DATA_PIN 6
#define MASTER 3
#define SLAVE 4



/**
//Multiplexer
//PCF85574
// addr : 0x20

//LCD Contorllers
//PCF2111T Master;
   addr : 0x01 1
   DLEN : 3
//PCF2111T Slave;
   addr : 0x01
   DLEN : 4

  Board  I2C / TWI pins
  Uno, A4 (SDA), A5 (SCL)


   ---CBUS PROCEEDURE---------------------------------
   DLEN High -> clock start -> data after 1 clock pulse

   When DATA bit 33 is a HIGH, the A-latches (BP1) are loaded. With DATA bit 33 LOW, the
**/

void LCD_Talk(unsigned char addr, char* myString, bool leadbyte ){
//  shiftOut(dataPin, clockPin, bitOrder, value)
  int i = 0, len = strlen(myString);

  //Write DLEN HIGH
  ////////////////////////////
  if (addr == MASTER){
   digitalWrite(CLOCK, HIGH);
   shiftOut(DATA_PIN, CLOCK, MSBFIRST,0x01);
   digitalWrite(CLOCK, LOW);
   delay(10);
   digitalWrite(CLOCK, HIGH);
   delay(10);
   digitalWrite(CLOCK, LOW);
   digitalWrite(PIN_M_DLEN, HIGH);
  }
  else if (addr == SLAVE){
   digitalWrite(CLOCK, HIGH);
   shiftOut(DATA_PIN, CLOCK, MSBFIRST,0x01);
   digitalWrite(CLOCK, LOW);
   delay(10);
   digitalWrite(CLOCK, HIGH);
   delay(10);
   digitalWrite(CLOCK, LOW);
   digitalWrite(PIN_S_DLEN, HIGH);
  }
  else{
    //do something, Think might just put IO Expander here?
    // so say, pass the data to wire type function to push and address normally
    //or
    digitalWrite(CLOCK, HIGH);
    shiftOut(DATA_PIN, CLOCK, MSBFIRST,addr);
    digitalWrite(CLOCK, LOW);
    delay(10);
    digitalWrite(CLOCK, HIGH);
    //digitalWrite //Data Pin to read acknowledgement... how? 
                 //Use another pin to monitor the state of the data buss?      
    }
 
  //Sending Leading byte
  if (leadbyte == true){
    digitalWrite(CLOCK, HIGH);
    delay(10);
    digitalWrite(CLOCK, LOW);
    delay(10);
    digitalWrite(CLOCK, HIGH);
    shiftOut(DATA_PIN,CLOCK,MSBFIRST,0); 
    digitalWrite(CLOCK, LOW); 
  }
  
  //Sending out the Data
  ///////////////////////////////
  for (i = 0; i < len; i++ ){
    char j = myString[i];
    digitalWrite(CLOCK, HIGH);
    shiftOut(DATA_PIN, CLOCK, MSBFIRST,j);
    digitalWrite(CLOCK, LOW);

  }
  //Write DLEN BACK LOW
  /////////////////////////
  if (addr == MASTER) digitalWrite(PIN_M_DLEN, LOW);
  else if (addr == SLAVE) digitalWrite(PIN_S_DLEN, LOW);
  else {
    
  }
}





void setup() { 
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Setup");

  
  pinMode(PIN_M_DLEN, OUTPUT);
  digitalWrite(PIN_M_DLEN, LOW);
  pinMode(PIN_S_DLEN, OUTPUT);
  digitalWrite(PIN_S_DLEN, LOW);
  digitalWrite(CLOCK, LOW);
  pinMode(DATA_PIN, OUTPUT);

  //pinMode(INTERRUPT, INPUT_PULLUP);


  //set Pin Modes (Add Later)
  //"pcf8574.begin();
  //pcf8574.write8(0xff)"
  
   Serial.println("\nprogram start ");

}
void loop() {
  // put your main code here, to run repeatedly:

}
