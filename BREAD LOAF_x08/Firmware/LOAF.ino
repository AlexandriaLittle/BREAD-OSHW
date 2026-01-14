#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#define chipSelect 4

String fileName = "tempData.txt";

#define THRM_ADR 8

byte commandSelect[3] = {1, 0, 0};

float temp1, temp2, temp3, temp4;

typedef union //Define a float that can be broken up and sent via I2C
{
  float number;
  uint8_t bytes[4];
} FLOATUNION_t;

FLOATUNION_t RX;

unsigned long log_interval = 1000;  // time between data points in milliseconds
unsigned long last_log_time = 0;
unsigned long counter = 0;

bool alreadyBegan = false;  // SD.begin() misbehaves if not first cal

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

  for(int i=0; i<5; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }

  File dataFile = SD.open(fileName, FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println("Time [s],Temp 1,Temp 2,Temp 3,Temp 4");
    dataFile.close();
    Serial.print("-> ");
  }
  Serial.println("Time [s],Temp 1,Temp 2,Temp 3,Temp 4");
  
  // wait for MAX chip to stabilize
  delay(500);
  
  last_log_time = millis();
}

void loop() {

  if(millis()-last_log_time >= log_interval && millis() <= 86400000){
    last_log_time = millis();

    // prime THRM for sending temp1 data
    Wire.beginTransmission(THRM_ADR);
    Wire.write(commandSelect, 3);
    Wire.endTransmission(THRM_ADR);
    
    Wire.requestFrom(THRM_ADR, 4);
    int i = 0;
    while(Wire.available()){
      RX.bytes[i] = Wire.read();
      i++;
    }
    temp1 = RX.number; 
    
    File dataFile = SD.open(fileName, FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.print(counter);
      dataFile.print(",");
      dataFile.println(temp1);
      dataFile.close();

      Serial.print("-> ");
    }

    // also print to serial monitor (for excel functionality)
    Serial.print(counter);
    Serial.print(",");
    Serial.println(temp1);
    counter++;
  }
}
