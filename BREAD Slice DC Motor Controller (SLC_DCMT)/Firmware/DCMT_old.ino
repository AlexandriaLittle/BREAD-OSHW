#include <Wire.h>
#include <SPI.h>

#define I2C_ADR 21 //Set this however you want

typedef union //Define a float that can be broken up and sent via I2C
{
 float number;
 uint8_t bytes[4];
} FLOATUNION_t;

// bunches of these
FLOATUNION_t RX_P1;
FLOATUNION_t RX_P2;
FLOATUNION_t RX_P3;
FLOATUNION_t RX_P4;

const int pwm1 = 6; 
const int pwm2 = 10;
const int dirSet1 = 9;
const int dirSet2 = 5;

int M1_EN = 1;
int M2_EN = 1;

int DC1, DC2;
int dir1 = 1;
int dir2 = 1;

int Command, arg1, arg2;

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // put your setup code here, to run once:
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(dirSet2, OUTPUT);
  pinMode(dirSet1, OUTPUT);

  //arbitrary start directions
  //digitalWrite(dirSet2, dir2);
  //digitalWrite(dirSet1, dir1);
  digitalWrite(dirSet2, HIGH);
  digitalWrite(dirSet1, HIGH);

  //mess with the brakes to experiment
  //digitalWrite(7, HIGH);
  //digitalWrite(11, HIGH);
  DC1 = 200;
  DC2 = 200;
}

void loop() {
  //directionSet();
  
  //if(M1_EN){
    analogWrite(pwm2, DC2);
    //bitBangPWM(pwm2);
  //}
  //if(M2_EN){
    analogWrite(pwm1, DC1);
    //bitBangPWM(pwm1);
  //}
  
}

void directionSet(){
  digitalWrite(dirSet2, dir2);
  digitalWrite(dirSet1, dir1);
}

void bitBangPWM(int pin){ //in case the speeds start gettin wonky
  digitalWrite(pin, HIGH);
  delay(300);
  digitalWrite(pin, LOW);
  delay(700);
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

}

void requestEvent() {

  //Send parameters if set to be requested
  // chnage these to make sense later
  if(1){
    for (int i = 0; i <=3; i++)
    {
      Wire.write(RX_P1.bytes[i]);
    }
  }
  if(1){
    for (int i = 0; i <=3; i++)
    {
      Wire.write(RX_P2.bytes[i]);
    }
  }
  if(1){
    for (int i = 0; i <=3; i++)
    {
      Wire.write(RX_P3.bytes[i]);
    }
  }
  if(1){
    for (int i = 0; i <=3; i++)
    {
      Wire.write(RX_P4.bytes[i]);
    }
  }
}

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

      // change
      int result = sscanf(inputString.c_str(), "%d,%d,%d", &Command, &arg1, &arg2);

      Serial.print(Command);
      Serial.print(", ");
      Serial.print(arg1);
      Serial.print(", ");
      Serial.println(arg2);


      switch(Command){

        //disperse gathered variables according to command issued
        case 0: //set-up command (nothing yet)
          break;
          
        case 1: // Motor select
          M1_EN = arg1;
          M2_EN = arg2;
          break;

        case 2: // Direction select
          dir1 = arg1;
          dir2 = arg2;
          break;

        case 3: // DC Select
          DC1 = map(arg1, 0, 100, 0, 255);
          DC2 = map(arg2, 0, 100, 0, 255);
          break;

        default:
          Serial.println("oopsie poopsie, that's not a command, silly");
      }
    }
  }
}
