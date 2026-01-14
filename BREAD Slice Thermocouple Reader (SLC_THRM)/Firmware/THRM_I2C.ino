#include "max6675.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#define MAXDO   12
#define MAXCS1   6
#define MAXCS2   7
#define MAXCS3   8
#define MAXCS4   9
#define MAXCLK   13

// initialize the Thermocouples
MAX6675 CH1(MAXCLK, MAXCS1, MAXDO);
MAX6675 CH2(MAXCLK, MAXCS2, MAXDO);
MAX6675 CH3(MAXCLK, MAXCS3, MAXDO);
MAX6675 CH4(MAXCLK, MAXCS4, MAXDO);

typedef union //Define a float that can be broken up and sent via I2C
{
  float number;
  uint8_t bytes[4];
} FLOATUNION_t;

FLOATUNION_t RX;

byte commandSelect[3];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin(13);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {

}

void requestEvent() {
  switch (commandSelect[0]) {
    case 1:
      RX.number = CH1.readCelsius();
      break;
    case 2:
      RX.number = CH2.readCelsius();
      break;
    case 3:
      RX.number = CH3.readCelsius();
      break;
    case 4:
      RX.number = CH4.readCelsius();
      break;
    default:
      RX.number = 0;
  }
  for (int i = 0; i <= 3; i++)
  {
    Wire.write(RX.bytes[i]);
  }
  commandSelect[0] = 0;
}

void receiveEvent(int howMany) {
  int i=0;
  while (Wire.available()) {
    commandSelect[i] = Wire.read();
    i++;
  }
}
