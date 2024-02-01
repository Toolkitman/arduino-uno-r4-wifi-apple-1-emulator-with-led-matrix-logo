// 12.01.2015 (c) P.Sieg simple Apple 1 emulator based on arduino_6502 c:\Users\Matteo\Downloads\a1logo.h
// project from miker00lz
// Released under GNU GPL V2

#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

uint8_t curkey = 0;
uint8_t iskey  = 0;

extern "C" {
  uint16_t getpc();
  uint8_t getop();
  void exec6502(int32_t tickcount);
  void reset6502();
  void serout(uint8_t val) {
    //Serial.print(val, HEX);
    //Serial.println();
    Serial.write(val);
  }
  uint8_t isakey() {
    if (Serial.available()) iskey  = 0x80;
    else iskey = 0;
    return(iskey);
  }
  uint8_t getkey() {
    curkey = Serial.read() & 0x7F;
    // make a-z => A-Z
    if ((curkey >= 97) && (curkey <= 122)) curkey = curkey - 0x20;
    return(curkey);
  }
  void clearkey() {
    curkey = 0;
  }
  void printhex(uint16_t val) {
    Serial.print(val, HEX);
    Serial.println();
  }
}

void setup () {
  Serial.begin(9600);
  Serial.println ();
  reset6502();
  matrix.begin();
}
const uint32_t a1logo [] = 
	{
		0x20000,
		0x7766525,
		0x72057000,
		66
	};


void loop () {
  exec6502(100); //if timing is enabled, this value is in 6502 clock ticks. otherwise, simply instruction count.
  matrix.loadFrame(a1logo);
  delay(500);
}

