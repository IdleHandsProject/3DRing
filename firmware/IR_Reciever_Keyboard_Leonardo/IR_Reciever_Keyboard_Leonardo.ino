/*
 IR Reciever side of the 3DRing code. This will be on the Leonardo. 
 IR Reciever PINOUT(on Leonardo) - (PWR - 6, GND - 7, SIG - 5)
 IR LED PINOUT(on Leonardo) - (Anode - 13, Cathode - 12) using a suitable Resistor in Series.
 
 Make sure the Arduino program is set to Leonardo in Tools/Board
 
 When recieving signal from ring it will either print "password" then hit enter, or it will mimic a mouse click
 
 For Dimmer Blank program on Ring.
 Uncomment "#define DEMO" to do the light brightness demo. Demo Only:
 Program will start only when you open a Serial Com port for the Leonardo. 
  You may send a number between 0 - 255 in the Serial port to change the light level
 */

#include <IRremote.h>
//#define DEMO
int RECV_PIN = 5;

IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;

int x = 150;

void setup()
{
  pinMode(12,OUTPUT);
  
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(12,LOW);
  
  //pinMode(2,OUTPUT);
  //digitalWrite(2,LOW);
  
  Serial.begin(9600);
  
  #ifdef DEMO
  while(!Serial);
   // Start the receiver
  Serial.println("---------3DRing-----------");
  Serial.println("Light Control Program V1.0");
  Serial.println("///////////////////////////");
  Serial.println("Type S to Being Program");
  delay(50);
  while (Serial.available() == 0);    //Check for data on the serial lines.
  Serial.println("Detecting Ring Light");
  irsend.sendSony(255, 12);
  delay(1000);
  irsend.sendSony(0, 12);
  delay(1000);
  irsend.sendSony(255, 12);
  delay(1000);
  irsend.sendSony(0, 12);
  delay(1000);
  irsend.sendSony(255, 12);
  delay(1000);
  Serial.println("Light Found!");
  delay(1000);
  Serial.println("Calibrating Light Intensity");
  for (int y = 0; y<25500; y++){
    irsend.sendSony(y/100, 12);
    Serial.println(y/100);
    y += 1000;
    delay(200);
  }
  Serial.println("Setting Light Level to 50%");
  x = 150;
  irsend.sendSony(x, 12);
  Serial.flush();
  Serial.flush();
  Serial.flush();
  Serial.println(Serial.available());
  Serial.println("Enter in light values from 0 - 255 to change light intensity");
  #endif
  irrecv.enableIRIn();
}
char dataIn;
void loop() {
  #ifdef DEMO
  if (Serial.available() > 0)    //Check for data on the serial lines.
  {   
 x = Serial.parseInt();
    dataIn = Serial.read();  //Get the character sent by the phone and store it in 'dataIn'.
    irsend.sendSony(x, 12);
   Serial.print("Sending value: ");
   Serial.println(x);
   irrecv.resume();
  }
  #endif
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    
    ////////////////Sean Login/////////////////////
    if (results.value == 0xA10){
      Keyboard.begin();
      Keyboard.print("password");
      delay(100);
      Keyboard.press(0xB0);
      delay(100);
      Keyboard.releaseAll();
      Keyboard.end();
    }
    ////////////////Tom Login//////////////////////
    if (results.value == 0xB20){
      Keyboard.begin();
      Keyboard.print("password");
      delay(100);
      Keyboard.press(0xB0);
      delay(100);
      Keyboard.releaseAll();
      Keyboard.end();
    }
    ///////////////Bear Login//////////////////////
    if (results.value == 0xC30){
      Keyboard.begin();
      Keyboard.print("password");
      delay(100);
      Keyboard.press(0xB0);
      delay(100);
      Keyboard.releaseAll();
      Keyboard.end();
    }
    /////////////Flip Login////////////////////////
    if (results.value == 0xD40){
      Keyboard.begin();
      Keyboard.print("password");
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
