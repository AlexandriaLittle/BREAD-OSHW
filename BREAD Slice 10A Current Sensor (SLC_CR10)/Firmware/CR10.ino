#include <Wire.h>
#include <SPI.h>

#define I2C_ADR 18 //Set this however you want

typedef union //Define a float that can be broken up and sent via I2C
{
 float number;
 uint8_t bytes[4];
} FLOATUNION_t;

FLOATUNION_t RX_P1;
FLOATUNION_t RX_P2;
FLOATUNION_t RX_P3;
FLOATUNION_t RX_P4;


#define CURR1 A0
#define CURR2 A1
#define CURR3 A2
#define CURR4 A3

double CH1, CH2, CH3, CH4;

//Default all channels enabled
int CH1_T = 1;
int CH2_T = 1;
int CH3_T = 1;
int CH4_T = 1;

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // put your setup code here, to run once:
  Wire.begin(I2C_ADR);                // join i2c bus with address #8
  //Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event

  inputString.reserve(50);

  Serial.begin(115200);

  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc
  delay(500);

}

void loop() {

  //Add some way to read and save 'Zero' current for each channel?
  
  int filterStrength = 50;
  //Read in all current values, low-pass 'em
  for(int i=0; i<filterStrength; i++){
    CH1 += analogRead(CURR1);
    CH2 += analogRead(CURR2);
    CH3 += analogRead(CURR3);
    CH4 += analogRead(CURR4);
  }

  CH1 = ((CH1/filterStrength)*0.0244379275)-12.4;
  CH2 = ((CH2/filterStrength)*0.0244379275)-12.4;
  CH3 = ((CH3/filterStrength)*0.0244379275)-12.4;
  CH4 = ((CH4/filterStrength)*0.0244379275)-12.4;

  //Print em
  Serial.print(CH1); 
  Serial.print(", ");
  Serial.print(CH2); 
  Serial.print(", ");
  Serial.print(CH3);
  Serial.print(", ");
  Serial.println(CH4);

  //test
  //Serial.print(CH1_T); 
  //Serial.print(", ");
  //Serial.print(CH2_T); 
  //Serial.print(", ");
  //Serial.print(CH3_T);
  //Serial.print(", ");
  //Serial.println(CH4_T);



  if (stringComplete) {
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  //delay(1000);
}

void receiveEvent(int howMany) {
  RX_P1.number = 0; RX_P2.number = 0; RX_P3.number = 0; RX_P4.number = 0;
  int ByteCount = 0;
  while (1 <= Wire.available()) { // loop through all but the last
    if (ByteCount == 0)
    {
      RX_P1.bytes[0] = Wire.read(); // receive a byte as character
    }
    else if (ByteCount == 1)
    {
      RX_P2.bytes[0] = Wire.read(); // receive a byte as character
    }
    else if (ByteCount == 2)
    {
      RX_P3.bytes[0] = Wire.read(); // receive a byte as character
    }
    else if (ByteCount == 3)
    {
      RX_P4.bytes[ByteCount] = Wire.read(); // receive a byte as character
    }
    ByteCount++;
  }
  stringComplete = true;
  CH1_T = RX_P1.number;
  CH2_T = RX_P2.number;
  CH3_T = RX_P3.number;
  CH4_T = RX_P4.number;

}

void requestEvent() {
  //needs changing
  
  RX_P1.number = CH1;
  RX_P2.number = CH2;
  RX_P3.number = CH3;
  RX_P4.number = CH4;
  
  //Send parameters if set to be requested
  if(CH1_T){
    for (int i = 0; i <=3; i++)
    {
      Wire.write(RX_P1.bytes[i]);
    }
  }

  if(CH2_T){
    for (int i = 0; i <=3; i++)
    {
      Wire.write(RX_P2.bytes[i]);
    }
  }

  if(CH3_T){
    for (int i = 0; i <=3; i++)
    {
      Wire.write(RX_P3.bytes[i]);
    }
  }

  if(CH4_T){
    for (int i = 0; i <=3; i++)
    {
      Wire.write(RX_P4.bytes[i]);
    }
  }
}


// This needs to be changed to I2C stuff?
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;

      CH1_T = inputString.substring(0).toInt();
      Serial.println("Got it!");
      CH2_T = inputString.substring(2).toInt();
      Serial.println("Got it!");
      CH3_T = inputString.substring(4).toInt();
      Serial.println("Got it!");
      CH4_T = inputString.substring(6).toInt();
      Serial.println("Got it!");
      
    }
  }
}
