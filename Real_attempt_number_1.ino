#include <Wire.h>


#define INTERRUPT 2
#define PIN_M_DLEN 3
#define PIN_S_DLEN 4

#define MASTER 3
#define SLAVE 4
int LCDAddr = 0x01;


//Multiplexer
//PCF85574
// addr : 0x20

//LCD Contorllers
//PCF2111T Master;
// addr : 0x01 1
// DLEN : 3
//PCF2111T Slave;
// addr : 0x01
// DLEN : 4

//Board  I2C / TWI pins
//Uno, A4 (SDA), A5 (SCL)


//CBUS PROCEEDURE
//DLEN High -> clock start -> data after 1 clock pulse

/** RISING EDGE OF TIMING MODUEL
 * cbus_send_bit - sends one bit over the bus
 * @host: the host we're using
 * @bit: one bit of information to send
 * 
 */

void LCD_Talk(int addr, char* Message ){ //will work on the message tramsission when talking established
                                        //don't think char will work hahaa
  int x = 0;
  if (addr = MASTER){
    digitalWrite(PIN_M_DLEN, HIGH);
  }
  else{
    digitalWrite(PIN_S_DLEN, HIGH);
  }
  Wire.beginTransmission(LCDAddr); // transmit to device #1
  Wire.write(x);
  
  Wire.endTransmission();

  
  if (addr = MASTER){
    digitalWrite(PIN_M_DLEN, LOW);
  }
  else{
    digitalWrite(PIN_S_DLEN, LOW);
  }
  

}

/**static void cbus_send_bit(struct cbus_host *host, unsigned bit)
{
  gpiod_set_value(host->dat, bit ? 1 : 0);
  gpiod_set_value(host->clk, 1);
  gpiod_set_value(host->clk, 0);
}**/

void setup() { 
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Setup");
  pinMode(PIN_M_DLEN, OUTPUT);
  digitalWrite(PIN_M_DLEN, LOW);
  pinMode(PIN_S_DLEN, OUTPUT);
  digitalWrite(PIN_S_DLEN, LOW);
  //pinMode(INTERRUPT, INPUT_PULLUP);


  //set Pin Modes (Add Later)
  //"pcf8574.begin();
  //pcf8574.write8(0xff)"
  
   Serial.println("\nprogram start ");

}

void loop() {

  char Message[] = "x to z"; // 5 bytes

  LCD_Talk(MASTER, Message);
  //Wire.beginTransmission(1);
  delay(100)
  buttonWait(9);
}
