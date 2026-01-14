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
3 - 
4 - 
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
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  display.clearDisplay();
  display.setCursor(0, 0); //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("");
  display.display();

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  transmit_Init(&dat);
}
 


void loop()
{
  if (radio.available()) // Check if there is Incoming Data in the radio.
  {

    display.clearDisplay();
    display.display();
    display.setCursor(0, 0); //oled display
    transmit_Init(&dat);
    
    Serial.print("Barcode:");
    Serial.print("\t");
    
    do{
      radio.read(&dat, sizeof(dat));//read from radio to get char array

      for(int i = 0; i < dat.j; i++){
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print(dat.Scanned[i]);
      display.display();
      Serial.print(dat.Scanned[i]);
      }
      
    }while(dat.j == 31);


    Serial.println("\t");


    Serial.println();
    display.clearDisplay();
    delay(10);
  }
}

