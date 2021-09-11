#include <PCF8574.h>


#include <Wire.h>
#include <Arduino.h>
#include <PCF8574.h>

PCF8574 pcf8574 (0x20); 

////////////////////////////////////

// INTERRUPT ROUTINE + FLAG
//
const int IRQPIN = 6;

volatile bool flag = false;

void pcf_irq()
{
  flag = true;
}

//////////////////////////////////////

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  pcf8574.begin();

  //set pin modes
  pcf8574.write8(0xff)

  //intterupt Pin (DARK GREEN) P6
  
  pinMode(IRQPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQPIN), pcf_irq, FALLING);
  
  //wait for serial monitor
  while (!Serial);            
  Serial.println("\nprogram start ");
}

void loop() {
   uint32_t now = millis();
  if (flag)
  {
    flag = false;
    int x = pcf8574.read8();
    Serial.print("READ:\t");
    Serial.print('\t');
    Serial.print(now);
    Serial.print('\t');
    Serial.println(x, HEX);
  }
  // do other things here
  delay(1000);
 

}
