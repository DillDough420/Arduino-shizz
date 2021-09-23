/*
Becker Runtime 0.01

//Multiplexer
//PCF85574
// addr : 0x20
//LCD Contorllers
//PCF2111T Master;
addr : 0x01 1
//DLEN : 3
//PCF2111T Slave;
// addr : 0x01
//  DLEN : 4
*/

// the setup function runs once when you press reset or power the board


/**
 * LCD storage
 * 
 * Defined in a 2 dimensional  array of LCD_MASTERLAVE[BackPlane][OutputData]
 * 
 * Going to define an array of 2rows,
 * 
 * Colum 0 is Backplane B
 * colum 1 is Backplane A
 *  
 * 
 * 
 * I2c communicaion, the busses are left high when no data is to be transmitted
 * 
 * 
 **/


// CBUS transmits 32 bits for pin activation, then 33rd bit for Backplane A(HIGH/ 1) or B(LOW / 0)




#define CBUS_DATA_STREAM 31
#define BACKPLANE_DATA 1

#define BACKPLANE_A HIGH
#define BACKPLANE_B LOW
#define INTERRUPT 2
#define DLEN_M 3
#define DLEN_S 4
#define CLOCK 5
#define DATA_PIN 6
#define MASTER 0
#define SLAVE 1
#define ACK LOW
// so i can change the clocking speed of the data.. I'm lazy
#define DELAY 1
bool ERRORFLAG = false;

char LCD_Master[BACKPLANE_DATA][CBUS_DATA_STREAM];

char LCD_Slave[BACKPLANE_DATA][CBUS_DATA_STREAM];


/**
void LCD_array(){
  char LCD_array[1][32] = {};
}*/

/**Controls CBUS routine
 *  sends out all data to relevant functions then shuts off comunication*/
void cbus_format_data(unsigned long data, char chip_select, char backplane)
{
 //CBUS START ROUTINE
  i2c_start_condition();
  i2c_addr_out(0x01);
  cbus_start_condition(chip_select);
  delay(DELAY);
  // start to transmit data
  cbus_send_data(data, CBUS_DATA_STREAM);
  cbus_backplane(backplane);
  digitalWrite(chip_select, LOW);
  clock_pulse();
  digitalWrite(DATA_PIN, HIGH );
  delay(DELAY);
  digitalWrite(CLOCK, HIGH);
}

/** sends that all vital S33 bit to control the backplane select*/
void cbus_backplane(char backplane){
digitalWrite(DATA_PIN, backplane);
delay(DELAY);
clock_pulse();
}


/** clock pulse, does what it says on the can */
void clock_pulse(){
  digitalWrite(CLOCK, HIGH);
  delay(DELAY);
  digitalWrite(CLOCK,LOW);
}


/** Controls chip select for CBUS */
void cbus_start_condition(char chip_select){
  digitalWrite(DATA_PIN, LOW);
  digitalWrite(chip_select, HIGH);
  delay(DELAY);
  clock_pulse();
}


void error(){
  //update_array(chip select, backplane select, )
  //We want this to flash a particular element on the LCD or even the backlight.
  //serial.Write "Error State"
}



//WIP
void i2c_io_handle (char addr, unsigned long data){
  i2c_start_condition();
  bool ack =i2c_addr_out(addr);
  if (ack == true){
    i2c_Transmit(data);
  }
  else{
      ERRORFLAG = true;
    
  }
    i2c_stop_condition();

}

bool i2c_addr_out(char addr){
  i2c_Transmit(addr);
  bool ack = i2c_get_ack();
  return ack;
}

/**
 * cbus_send_data - sends @len amount of data over the bus
 *sends first bit of a byte, then shifts bit  1 place with the whole 1 << (i - 1)
 * @data: the data to send
 * @len: size of the transfer
 */
void cbus_send_data(unsigned data, char len)
{
  int i;
  for (i = len; i > 0; i--)
    cbus_send_bit(data & (1 << (i - 1)));
}

/**
 * cbus_send_bit - sends one bit over the bus
 * @bit: one bit of information to send
 *remebering one clock cycle is requred per bit.
 *so data high or low is inputted, then clock is pulsed up and down
 */
void cbus_send_bit( char bit )
{
  digitalWrite(DATA_PIN, bit);
  delay(DELAY);
  clock_pulse();
  delay(DELAY);
}

//Start sequece for i2c
void i2c_start_condition()
{
  digitalWrite(DATA_PIN,LOW);
  delay(DELAY);
  digitalWrite(CLOCK,LOW);
  delay(DELAY);
}

//stop condition for i2c
void i2c_stop_condition()
{
  digitalWrite(DATA_PIN, LOW);
  delay(DELAY);
  digitalWrite(CLOCK, HIGH);
  delay(DELAY);
  digitalWrite(DATA_PIN, HIGH);
  delay(DELAY);
}



//I2C trasmitting 8 bits to slave
bool i2c_Transmit(unsigned long data)
{
   for (int i=0; i<8; i++)
  { if (data & 0x80){
      digitalWrite(DATA_PIN, HIGH);
    }
    else
    {
      digitalWrite(DATA_PIN, LOW);
    }
    clock_pulse();
    data <<= 1;
    delay(DELAY);
  }
  bool ack = i2c_get_ack();
  return ack;
}

bool i2c_get_ack()
{
  digitalWrite(DATA_PIN, HIGH);
  digitalWrite(CLOCK, HIGH);
  delay(DELAY);
  bool ack = digitalRead(DATA_PIN);
  if (ack == ACK){
    return true;
  }
  else{
    return false;
  }
}

//Function to pause till button pressed, cause i hate infiniet loops
void buttonWait(int buttonPin){
  int buttonState = 0;
  while(1){
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      return;
    }
  }
}


/** Hopefully Clears the Screen
 * by converting the whole array to 0's
*/
void clear_LCD(){
  char * LCD_array[1][1][CBUS_DATA_STREAM] = {};
//  LCD_UPDATE(LCD_array);
}

//Rewritee this function to accomedate global Master and Slave arrays declared t top of statement
//might still have to pass binary ahahah
/**This Meaty Function breaks up the LCD array into 
 * its component parts, and sends them to be formatted
 * 
 * It splits the Master and Slave sections into two parts
 * then splits Master and Slave in to Backplane A and B.
 * 
 * Converts the saved array data into a binary figure using
 * place shifting, each next bit is moved over by 10 to result
 * in a 32 bit long binary string of 1's and 0's, which is
 * sent to the binary to decimal to convert it to a single
 * byte to be sent to the display
 *  
 **/

void LCD_UPDATE(char LCD_array[1][1][CBUS_DATA_STREAM]){


int binaryToDecimal(int n)
{
    int num = n, dec_value = 0, base = 1, temp = num;

    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 2;
    }
 
    return dec_value;
}

/** Initialises pins and shit */
void setup() {
  // initializing pins. 
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(DLEN_M, OUTPUT);
  pinMode(DLEN_S, OUTPUT);
  //write all pins Low
  digitalWrite(CLOCK, HIGH);
  digitalWrite(DATA_PIN, HIGH);
  digitalWrite(DLEN_M, LOW);
  digitalWrite(DLEN_S,LOW);

  Serial.print("Program Start");
  clear_LCD();
 // LCD_UPDATE(LCD_array);






}


// the loop function runs over and over again forever
void loop() {

  char data, len = '1';
  if (ERRORFLAG == true)
  {
    error();
  }


  for (int i = 0; i < 126; i++ ){
    cbus_send_data(data, len );
  }
  
}
