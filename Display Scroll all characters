#define PIN_M_DLEN 3
#define PIN_S_DLEN 6
#define PIN_CLB  4
#define PIN_DATA 5

#define DATA_COUNT 4
byte displayData[2][DATA_COUNT] = {{0,0,0,0},{0,0,0,0}};

void setup() 
{
  Serial.begin(9600);
  Serial.println("Setup");
  pinMode(PIN_M_DLEN, OUTPUT);
  digitalWrite(PIN_M_DLEN, LOW);
  pinMode(PIN_S_DLEN, OUTPUT);
  digitalWrite(PIN_S_DLEN, LOW);
  pinMode(PIN_CLB , OUTPUT);
  digitalWrite(PIN_CLB, LOW);
  pinMode(PIN_DATA, OUTPUT);
  digitalWrite(PIN_DATA, LOW);
  buttonWait(9);
  
}

void shiftBit(byte value){
  digitalWrite(PIN_CLB, HIGH);
  digitalWrite(PIN_DATA, value);
  digitalWrite(PIN_CLB, LOW);
}

void shiftByte(byte value){
  byte tmp = value;
  for(byte c=0; c<8; c++){
    shiftBit(tmp & 1);
    tmp = tmp >> 1;
  }
}

byte activeBP = 0;
void updateDisplayM(){
  activeBP ^= 0x01;
  
  digitalWrite(PIN_M_DLEN, HIGH);
  // leading zero
  shiftBit(0);
  
  for(byte c=0; c<DATA_COUNT; c++){
    shiftByte(displayData[activeBP][c]);
  }
  
  // load bit
  shiftBit(activeBP);
  
  digitalWrite(PIN_M_DLEN, LOW);

  // load pulse
  shiftBit(0);

}

void updateDisplayS(){
  activeBP ^= 0x01;
  
  digitalWrite(PIN_S_DLEN, HIGH);
  // leading zero
  shiftBit(0);
  
  for(byte c=0; c<DATA_COUNT; c++){
    shiftByte(displayData[activeBP][c]);
  }
  
  // load bit
  shiftBit(activeBP);
  
  digitalWrite(PIN_S_DLEN, LOW);

  // load pulse
  shiftBit(0);

}

void buttonWait(int buttonPin){
  int buttonState = 0;
  while(1){
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
      return;
    }
  }
}

unsigned long last = 0;
void loop() {
  int x = 0, y = 0, i = 0; // x is BackPlane Y is Seg, 255 is magic number of bits per division
  buttonWait(9); // wait for button press on pin 
  Serial.println("Top of loop");
  for (x = 0; x !=2; x++){
    for (y = 0; y != 4; y++){
      for (i = 0; i != 256; i++){
        displayData[x][y] = i;
        updateDisplayS();
        Serial.print("\nLoopCounter value = ");
        Serial.print(x);
        Serial.print(y);
        Serial.print(i);
      }
    }
  }
}
