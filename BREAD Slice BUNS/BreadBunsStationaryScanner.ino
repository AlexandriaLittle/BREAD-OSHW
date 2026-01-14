#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/* PIN Assignments
Arduino Nano
digital:
2 -
3 - Barcode Scanner Serial Rx from scanner
4 - Barcode Scanner Serial Tx to scanner
5 -
6 -
7 -
8 - 
9 - RF24 radio -ce
10- RF24 radio -csn
11- RF24 radio -mosi
12- RF24 radio -miso
13- RF24 radio -sck

analog:
0-
1-
2-
3-
4- SDA -Display
5- SCL -Display
6-
7-
*/

//RF24 radio
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

//Barcode Scanner Serial
SoftwareSerial mySerial(3, 4); // RX, TX
 
//Display
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
//struct for combining data
struct transmitData{
  uint8_t j;
  char Scanned[31];
};

void transmit_Init(struct transmitData* Transmitted){
  for(int i = 0; i <= 31; i++){
    Transmitted -> Scanned[i] = 0;
  }
  Transmitted -> j = 0;
}


struct transmitData dat;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600); // set the data rate for the SoftwareSerial port
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  display.clearDisplay();
  display.display();

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  transmit_Init(&dat);
}
 


void loop()
{
  if (mySerial.available()) // Check if there is Incoming Data in the Serial Buffer.
  {
    Serial.print("Barcode:");
    Serial.print("\t");
    
    display.setCursor(0, 0); //oled display
    transmit_Init(&dat);
    while (mySerial.available()) // Keep reading Byte by Byte from the Buffer till the Buffer is empty
    {
      char input = mySerial.read(); // Read 1 Byte of data and store it in a character variable
      
      if(dat.j < 31){
        dat.Scanned[dat.j] = input;
        dat.j++;
        Serial.print(input);
      }else{
        radio.write(&dat, sizeof(dat));
        transmit_Init(&dat);
        dat.Scanned[dat.j] = input;
        dat.j++;
        Serial.print(input);
      }
 
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print(input);
    }
    display.display();
    display.clearDisplay();

    Serial.println("\t");

    radio.write(&dat, sizeof(dat));
    delay(10);
  }
}
