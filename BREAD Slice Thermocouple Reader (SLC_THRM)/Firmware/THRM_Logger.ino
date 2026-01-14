/*
 * Code works with SD card shield for SLC_THRM
 */

#include "max6675.h"
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#define MAXDO   10
#define MAXCS1   6
#define MAXCS2   7
#define MAXCS3   8
#define MAXCS4   9
#define MAXCLK   5

Sd2Card card;
SdVolume volume;
SdFile root;

#define chipSelect 4
#define cardDetect 3

String fileName = "tempData.txt"; // SD library only supports up to 8.3 names

double temp1, temp2, temp3, temp4;

int CH1_T = 1;
int CH2_T = 1;
int CH3_T = 1;
int CH4_T = 1;

// initialize the Thermocouples
MAX6675 CH1(MAXCLK, MAXCS1, MAXDO);
MAX6675 CH2(MAXCLK, MAXCS2, MAXDO);
MAX6675 CH3(MAXCLK, MAXCS3, MAXDO);
MAX6675 CH4(MAXCLK, MAXCS4, MAXDO);

unsigned long log_interval = 1000;  // time between data points in milliseconds
unsigned long last_log_time = 0;
unsigned long counter = 0;

bool alreadyBegan = false;  // SD.begin() misbehaves if not first call

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);

  pinMode(cardDetect, INPUT);

  initializeCard();

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
    
    temp1 = CH1.readCelsius();
    temp2 = CH2.readCelsius();
    temp3 = CH3.readCelsius();
    temp4 = CH4.readCelsius(); 
    
    File dataFile = SD.open(fileName, FILE_WRITE);

    // if the file is available, write to it:
    if (dataFile) {
      dataFile.print(counter);
      dataFile.print(",");
      dataFile.print(temp1);
      dataFile.print(",");
      dataFile.print(temp2);
      dataFile.print(",");
      dataFile.print(temp3);
      dataFile.print(",");
      dataFile.println(temp4);
      dataFile.close();

      Serial.print("-> ");
    }

    // also print to serial monitor (for excel functionality)
    Serial.print(counter);
    Serial.print(",");
    Serial.print(temp1);
    Serial.print(",");
    Serial.print(temp2);
    Serial.print(",");
    Serial.print(temp3);
    Serial.print(",");
    Serial.println(temp4);

    counter++;
  }
}

void initializeCard(void)
{
  Serial.print("\nInitializing SD card...");

  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    while (1);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }

  // print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Unknown");
  }

  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }

  Serial.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());

  Serial.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print("Volume size (Kb):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);

  Serial.println("\nFiles found on the card (name, date and size in bytes): ");
  root.openRoot(volume);

  // list all files in the card with date and size
  root.ls(LS_R | LS_DATE | LS_SIZE);
}
