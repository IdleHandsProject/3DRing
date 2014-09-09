/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 10;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    
    ////////////////Sean Login/////////////////////
    if (results.value == 0xA10){
      Keyboard.begin();
      Keyboard.print("Seanhodgins");
      delay(100);
      Keyboard.press(0xB0);
      delay(100);
      Keyboard.releaseAll();
      Keyboard.end();
    }
    ////////////////Tom Login//////////////////////
    if (results.value == 0xB20){
      Keyboard.begin();
      Keyboard.print("3dewitt");
      delay(100);
      Keyboard.press(0xB0);
      delay(100);
      Keyboard.releaseAll();
      Keyboard.end();
    }
    ///////////////Bear Login//////////////////////
    if (results.value == 0xC30){
      Keyboard.begin();
      Keyboard.print("bearlabs");
      delay(100);
      Keyboard.press(0xB0);
      delay(100);
      Keyboard.releaseAll();
      Keyboard.end();
    }
    /////////////Flip Login////////////////////////
    if (results.value == 0xD40){
      Keyboard.begin();
      Keyboard.print("arduinos");
      delay(100);
      Keyboard.press(0xB0);
      delay(100);
      Keyboard.releaseAll();
      Keyboard.end();
    }
    ///////////Mouse Click///////////////////////
    if (results.value == 0x000){
      Mouse.begin();
      delay(100);
      Mouse.click();
      delay(100);
      Mouse.end();
    }
    
    irrecv.resume(); // Receive the next value
  
}
  
}
