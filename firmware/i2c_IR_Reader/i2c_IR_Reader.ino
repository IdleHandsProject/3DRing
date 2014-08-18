// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup()
{
  
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  digitalWrite(A2,LOW);
  digitalWrite(A3,HIGH);
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(19200);  // start serial for output
}

void loop()
{
  Wire.requestFrom(0, 6);    // request 6 bytes from slave device #2

  while (Wire.available())   // slave may send less than requested
  {
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }

  delay(500);
}
