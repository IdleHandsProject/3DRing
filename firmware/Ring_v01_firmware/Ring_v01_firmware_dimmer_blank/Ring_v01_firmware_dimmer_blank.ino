
/*
  3DRing Firmware. Blanks out light with Button Push Version - Used with DEMO of Reciever
  Using SparkFun "GPS Breakout Board" https://www.sparkfun.com/products/11818 Swap wires Rx with Tx on Small cable. Pin 6 of the GPS breakout Board goes to Ground on the 3.3V FTDI ( https://www.sparkfun.com/products/9873 )
  To swap Rx/Tx, swap wires 2 and 3 in reference to the GPS breakout. 
  
  Libraries included in zip go in your Arduino/libraries location. Just drag the whole folder into it.
  Make sure the Arduino program is set to "Arduino Pro or Pro mini (3.3V 8Mhz)" in Tools/Board.
 */

#include <IRremote.h>
#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>

int RECV_PIN = 5;
#define PIN 2


IRrecv irrecv(RECV_PIN);
IRsend irsend;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
decode_results results;
CapacitiveSensor   cs_9_10 = CapacitiveSensor(9, 10);
CapacitiveSensor   cs_11_12 = CapacitiveSensor(11, 12);
int R, G, B = 150;
uint16_t RH, GH, BH = 150;
int x = 150;
char dataIn;
void setup()
{
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  Serial.begin(9600);
  strip.begin();
  strip.show();
  //cs_9_10.reset_CS_AutoCal();
  // Start the receiver
  irrecv.enableIRIn();

}

void loop() {
  if (Serial.available() > 0)    //Check for data on the serial lines.
  {   
    x = Serial.parseInt();
    dataIn = Serial.read();  //Get the character sent by the phone and store it in 'dataIn'.
    irsend.sendSony(x, 12);
   
  }
  //long start = millis();
  //long total1 =  cs_9_10.capacitiveSensor(30);
  //long total2 =  cs_11_12.capacitiveSensor(30);
  long total1 = 30;
  long total2 = 30;
  //Serial.print(millis() - start);        // check on performance in milliseconds
  //Serial.print("\t");                    // tab character for debug windown spacing

  //Serial.print(total1);                  // print sensor output 1
  //Serial.print("\t");
  //Serial.println(total2);
  x = results.value;
  colorWipe(strip.Color(x, x, x), 10);
  //strip.setPixelColor(1, 0xFF,0xFF,0xFF);
  //strip.show();
  //delay(100);
  if (total1 > 150){
  //for (int i = 0; i < 3; i++) {
    irsend.sendSony(0xb20, 12); // Sony TV power code
    Serial.println("Sending");
    colorWipe(strip.Color(255, 0, 0), 10);
    delay(100);
    //strip.Color(255,255,255);
    
  //}
  }
  if (total2 > 30000){
  //for (int i = 0; i < 3; i++) {
    irsend.sendSony(0x000, 12); 
    Serial.println("Sending");
    colorWipe(strip.Color(0, 255, 0), 10);
    delay(100);
    
  //}
  }
  
  if (irrecv.decode(&results)) {
    Serial.println(results.value);
    if (results.value == 0x000) {
      RH++;
      colorWipe(strip.Color(0, 0, 0), 10);
      delay(500);
    }
    //RH = String(R, HEX);
    //BH = String(B, HEX);
    //GH = String(G, HEX);


    irrecv.resume(); // Receive the next value
    
  

  }



}


void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}


uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
