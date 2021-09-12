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

#define CBUS_ADDR_BITS	3
#define CBUS_REG_BITS	5

#define INTERRUPT 2
#define DLEN_M 3
#define DLEN_S 4
#define CLOCK 5
#define DATA_PIN 6
#define MASTER 3
#define SLAVE 4
#define ACK LOW

void cbus_format_data(unsigned data, unsigned chip_select)
{

  i2c_start_condition();
  digitalWrite(chip_select, HIGH);




  digitalWrite(chip_select, LOW);

  





}


/**
 * cbus_send_data - sends @len amount of data over the bus
 * @host: the host we're using
 * @data: the data to send
 * @len: size of the transfer
 */
void cbus_send_data(unsigned data, unsigned len)
{
	int i;

	for (i = len; i > 0; i--)
		cbus_send_bit(data & (1 << (i - 1)));
}


/**
 * cbus_send_bit - sends one bit over the bus
 * @bit: one bit of information to send
 */
void cbus_send_bit( unsigned bit )
{
  digitalWrite(DATA_PIN, bit);
  delay(1);
	digitalWrite(CLOCK, HIGH);
  delay(1);
	digitalWrite(CLOCK, LOW);
  delay(1);
}

/**
 * cbus_receive_bit - receives one bit from the bus
 * @host: the host we're using
 */
static int cbus_receive_bit(struct cbus_host *host)
{
	int ret;
  digitalWrite(DATA_PIN, HIGH);
  delay(1);
	digitalWrite(CLOCK, HIGH);
  delay(1);
	ret = digitalRead(DATA_PIN);
	digitalWrite(CLOCK, LOW);
  delay(1);
	return ret;
}

//Start sequece for i2c
void i2c_start_condition()
{
  digitalWrite(DATA_PIN, HIGH);
  delay(1);
	digitalWrite(CLOCK, HIGH);
  delay(1);
  digitalWrite(DATA_PIN,LOW);
  delay(1);
  digitalWrite(CLOCK,LOW);
  delay(1);
}

//stop condition for i2c
void i2c_stop_condition()
{
  digitalWrite(DATA_PIN, LOW);
  delay(1);
  digitalWrite(CLOCK, HIGH);
  delay(1);
  digitalWrite(DATA_PIN, HIGH);
  delay(1);
}


//I2C trasmitting 8 bits to slave
bool i2c_Transmit(unsigned addr, unsigned data)
{
   for (int i=0; i<8; i++)
  {
    if (data & 0x80){
      digitalWrite(DATA_PIN, HIGH);
    }
    else
    {
      digitalWrite(DATA_PIN, LOW);
    }
    digitalWrite(CLOCK, HIGH);
    delay(1);
    digitalWrite(CLOCK, LOW);
    data <<= 1;
    delay(1);
  }
  bool ack = i2c_get_ack();
  return ack;
}

bool i2c_get_ack()
{
  digitalWrite(DATA_PIN, HIGH);
  digitalWrite(CLOCK, HIGH);
  delay(1);
  bool ack = digitalRead(DATA_PIN);
  digitalWrite(CLOCK, LOW);
  return ack;
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

void setup() {
  // initializing pins. 
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(DLEN_M, OUTPUT);
  pinMode(DLEN_S, OUTPUT);
  //write all pins Low
  digitalWrite(CLOCK, LOW);
  digitalWrite(DATA_PIN, LOW);
  digitalWrite(DLEN_M, LOW);
  digitalWrite(DLEN_S,LOW);

  Serial.print("Program Start");






}


// the loop function runs over and over again forever
void loop() {
  char data, len = '1';

  for (int i = 0; i < 126; i++ ){
    cbus_send_data(data, len );
  }
  
}
