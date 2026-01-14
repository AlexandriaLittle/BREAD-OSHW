#include "BREAD_DAQ.h"

uint32_t curChannel;

int channelPins[] = {0,1,2,3,A6,A7};     //First four channels are in the AD7193, the last two go to the terminals
int sensorType[] = {THERMOCOUPLE_K,THERMOCOUPLE_K,THERMOCOUPLE_K,THERMOCOUPLE_K,PHOTORESISTOR,PHOTORESISTOR};  //Tracks what each channel is currently set to read, defaults given here
int output[] = {CELSIUS,CELSIUS,CELSIUS,CELSIUS,LUX,LUX};    //Tracks current format of output for each channel
bool activePins[] = {true,false,false,false,false,false};          //Tracks which channels are currently being used, 0 indicates not active

LiquidCrystal lcd(0,1,5,6,7,8);   //Pins for controlling LCD screen

// Define RTC objects
RTClib myRTC;
DS3231 setRTC;
bool setTime = 0; // If 1 time will be set in the setup loop. Leave 0 once time is set

// Define variables for SD filename
char* filename;
File dataFile;
bool SDconn = 0;

// Define CAN bus
MCP_CAN CAN(CAN_SPI_CS);
bool CANconn = 0;

void setup() {
  //Serial.begin(9600);

  
  //For setting time on RTC
  if (setTime == 1){
    byte DoW = 2;
    byte Year = 24;
    byte Month = 11;
    byte Date = 19;
    byte Hour = 19;
    byte Minute = 43;
    byte Second = 0;
    setRTC.setDoW(DoW);
    setRTC.setYear(Year);
    setRTC.setMonth(Month);
    setRTC.setDate(Date);
    setRTC.setHour(Hour);
    setRTC.setMinute(Minute);
    setRTC.setSecond(Second);
  } 
  
  pinMode(A0,OUTPUT);

  curChannel = 0;
  //Serial.print("Started\n");
  // put your setup code here, to run once:
  AD7193_setup();

  //Write sensor type to display
  lcd.clear();
  delay(1000);
  lcd.begin(16,2);

  SDsetup();
  
  initializeCAN();

 

  changeLabel();

  //Sets up button interrupt pins
  pinMode(SW1pin, INPUT_PULLUP);
  pinMode(SW2pin, INPUT_PULLUP);
  //pinMode(A6,INPUT);
  //pinMode(A7,INPUT);

  //Enable interrupts on the PC port
  PCICR |= B0010;

  //Enable interrupts on pins A1 and A2
  PCMSK1 |= B0110;
}

void loop() {
  static float data;
  //Serial.print("Loop\n");
  for(uint32_t j = 0; j < 6; j++){
    //Go through each pin, only read from it if it is active
    //bool isActive = activePins[j];

    if(activePins[j]){
      //Read from pin and calculate what the voltage is
      data = readSensor(j);

      if(curChannel == j){
        displayData(data);
      }

      sendCANData(&data,j);
      SDwrite(data,j);

      delay(500);
    }
  }

  checkCAN();
  delay(1000);

  //************************************************************************************
  //                          DO NOT DELETE DUPLICATE
  //
  // The code does not like having a single explicit call to SDwrite() or lcd.print().
  // Having the duplicate makes it work. Edit at your own risk
  //************************************************************************************
  for(uint32_t j = 0; j < 6; j++){
    //Go through each pin, only read from it if it is active
    //bool isActive = activePins[j];

    if(activePins[j]){
      //Read from pin and calculate what the voltage is
      data = readSensor(j);

      //Only write to LCD screen if it is the current channel being displayed
      if(curChannel == j){
        displayData(data);
      }

      sendCANData(&data,j);
      SDwrite(data,j);

      delay(500);
    }
  }

  delay(1000);
}

//Reads at the channel given for the type of sensor given
float readSensor(int channelNumber){
  switch(sensorType[channelNumber]){
    case THERMOCOUPLE_K:
      return thermocoupleKOutput(channelNumber);
      break;
    case CURRENT:
      return currentOutput();
      break;
    case PHOTORESISTOR:
      return photoresistorOutput(channelNumber);
      break;
    default:
      return -1;
      break;
  }
}
