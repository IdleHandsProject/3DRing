// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>
#include "BlinkM_funcs.h"
#define addr 0x09
void setup()
{
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  digitalWrite(A2,LOW);
  digitalWrite(A3,HIGH);
  BlinkM_beginWithPower();  
  BlinkM_stopScript( addr ); 
  delay(100);
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(19200);
  
}

byte o = 0;
byte r,g,b = 2;
void loop()
{
  
  
  // stop transmitting
  BlinkM_setRGB(addr, r,g,b );
  o++;
  delay(100);
}
