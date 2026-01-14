// Include the AccelStepper Library
#include <AccelStepper.h>
#include <Wire.h>
#include <SPI.h>

#define I2C_ADR 20 //Set this however you want

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

// Define pin connections
const int dirPin1 = 6;
const int stepPin1 = 5;
const int dirPin2 = 8;
const int stepPin2 = 7;
const int dirPin3 = 10;
const int stepPin3 = 9;
const int dirPin4 = 12;
const int stepPin4 = 11;

// Variables for command parameters
int inputSteps1 = 0;
int inputSteps2 = 0;
int inputSteps3 = 0;
int inputSteps4 = 0;

int motornum, mtrMaxSpeed, Accel, mtrSpeed;
int pos1, pos2, pos3, pos4;

int F1;
int F2;
int F3;
int F4;

int F1_R=1;
int F2_R=1;
int F3_R=1;
int F4_R=1;

int Command;
int arg1;
int arg2;
int arg3, arg4, arg5;

byte motorMask; // which motors to use. bits 4-7 unused, bits 3-0 are motors 1-4 respectively for readability.
byte mode; //only valid inputs for now are 1, 2, 3. 


// Define motor interface type
#define motorInterfaceType 1

// Creates an instance
AccelStepper CH1(motorInterfaceType, stepPin1, dirPin1);
AccelStepper CH2(motorInterfaceType, stepPin2, dirPin2);
AccelStepper CH3(motorInterfaceType, stepPin3, dirPin3);
AccelStepper CH4(motorInterfaceType, stepPin4, dirPin4);

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {

  Wire.begin(I2C_ADR);            // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent);   // register event

  inputString.reserve(50);

  Serial.begin(115200);

  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc
  delay(500);

  motorMask = 15; //all on by default (15 is the max.)

  config(1, 1000, 50, 200); //put some default parameters here
  config(2, 1000, 50, 200); //put some default parameters here
  config(3, 1000, 50, 200); //put some default parameters here
  config(4, 1000, 50, 200); //put some default parameters here
 
  setStep(0,0,0);
}

void loop() {

  // rerun config constantly in case values change
  config(motornum, mtrMaxSpeed, Accel, mtrSpeed);
  //getFeedback();

  // check to make sure no mode overlap-- stop if yes
  switch(mode){
    case 1:
      //do a mode
      DCMode(motorMask);
      break;
    case 2:
      //do another
      ServoMode(motorMask, pos1, pos2, pos3, pos4); //make configurable
      break;
    case 3:
      //final one
      StepMode(motorMask, inputSteps1, inputSteps2, inputSteps3, inputSteps4); //make configurable
      break;
    default:
      //do nothing
      Serial.println("Please select only one mode");
      break;
  }

  if (stringComplete) {
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

}

void config(int channel, int maxspeed, int acc, int setspeed){
  
  switch(channel){
    case 1:
      CH1.setMaxSpeed(maxspeed); //1000
      CH1.setAcceleration(acc); //50
      CH1.setSpeed(setspeed); //100
      break;

    case 2:
      CH2.setMaxSpeed(maxspeed); //1000
      CH2.setAcceleration(acc); //50
      CH2.setSpeed(setspeed); //100
      break;

    case 3:
      CH3.setMaxSpeed(maxspeed); //1000
      CH3.setAcceleration(acc); //50
      CH3.setSpeed(setspeed); //100
      break;

    case 4:
      CH4.setMaxSpeed(maxspeed); //1000
      CH4.setAcceleration(acc); //50
      CH4.setSpeed(setspeed); //100
      break;
  }
}

void DCMode(byte mask){
  
  if(bitRead(mask, 3)){
    CH1.runSpeed();
  }
  if(bitRead(mask, 2)){
    CH2.runSpeed();
  }
  if(bitRead(mask, 1)){
    CH3.runSpeed();
  }
  if(bitRead(mask, 0)){
    CH4.runSpeed();
  }
  
}

void ServoMode(byte mask, int loc1, int loc2, int loc3, int loc4){

  //might need additional control stuff
  
  CH1.moveTo(loc1);
  CH2.moveTo(loc2);
  CH3.moveTo(loc3);
  CH4.moveTo(loc4);
  
  // Move the motor one step
  if(bitRead(mask, 3)){
    CH1.run();
  }
  if(bitRead(mask, 2)){
    CH2.run();
  }
  if(bitRead(mask, 1)){
    CH3.run();
  }
  if(bitRead(mask, 0)){
    CH4.run();
  }
  
}

void StepMode(byte useMask, int steps1, int steps2, int steps3, int steps4){

  int maxSteps = steps1;
  int steps[4] = {steps1, steps2, steps3, steps4};

  //determine the max amount of steps for loop length
  for(int j=0; j<4; j++){
    if(maxSteps<steps[j]){
      maxSteps = steps[j];
    }
  }

  CH1.moveTo(steps1);
  CH2.moveTo(steps2);
  CH3.moveTo(steps3);
  CH4.moveTo(steps4);

  
  //loop through max steps, only step when activated or below required steps
  for(int i=0; i<maxSteps; i++){
    if(bitRead(useMask, 3) && (i<steps1)){
      CH1.run();
    }
    if(bitRead(useMask, 2) && (i<steps2)){
      CH2.run();
    }
    if(bitRead(useMask, 1) && (i<steps3)){
      CH3.run();
    }
    if(bitRead(useMask, 0) && (i<steps4)){
      CH4.run();
    }
    Serial.print("l o o p ");
    Serial.println(i);
    delay(10);
  }

  //set steps to zero so it needs to be manually reset?
  inputSteps1 = 0;
  inputSteps2 = 0;
  inputSteps3 = 0;
  inputSteps4 = 0;
}

//Function to go grab feedback paths
void getFeedback(){
  
  F1 = analogRead(A0);
  F2 = analogRead(A1);
  F3 = analogRead(A2);
  F4 = analogRead(A3);

  Serial.print(F1); 
  Serial.print(", ");
  Serial.print(F2); 
  Serial.print(", ");
  Serial.print(F3);
  Serial.print(", ");
  Serial.println(F4);
  
}

void setStep(int i, int j, int k){
  // i, j, k == MS1, MS2, MS3
  digitalWrite(13, k);
  digitalWrite(A6, i);
  digitalWrite(A7, j);
}

void home(int axis, int path){
  
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
  if(F1_R){
    for (int i = 0; i <=3; i++)
    {
      Wire.write(RX_P1.bytes[i]);
    }
  }
  if(F2_R){
    for (int i = 0; i <=3; i++)
    {
      Wire.write(RX_P2.bytes[i]);
    }
  }
  if(F3_R){
    for (int i = 0; i <=3; i++)
    {
      Wire.write(RX_P3.bytes[i]);
    }
  }
  if(F4_R){
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


      int result = sscanf(inputString.c_str(), "%d,%d,%d,%d,%d,%d", &Command, &arg1, &arg2, &arg3, &arg4, &arg5);

      Serial.print(Command);
      Serial.print(", ");
      Serial.print(arg1);
      Serial.print(", ");
      Serial.print(arg2);
      Serial.print(", ");
      Serial.print(arg3);
      Serial.print(", ");
      Serial.print(arg4);
      Serial.print(", ");
      Serial.println(arg5);

      switch(Command){

        //disperse gathered variables according to command issued
        case 0: //set-up command
          motornum = arg1;
          mtrMaxSpeed = arg2;
          Accel = arg3;
          mtrSpeed = arg4;
          break;
          
        case 1: //DC Mode command
          mode = Command;
          motorMask = arg1;
          break;

        case 2: //Servo Mode command
          mode = Command;
          motorMask = arg1;
          pos1 = arg2;
          pos2 = arg3;
          pos3 = arg4;
          pos4 = arg5;
          break;

        case 3: //Single step command
          mode = Command;
          motorMask = arg1;
          inputSteps1 = arg2;
          inputSteps2 = arg3;
          inputSteps3 = arg4;
          inputSteps4 = arg5;
          break;

        default:
          mode = Command;
          Serial.println("oopsie poopsie, that's not a command, silly");
          
      }
    }
  }
}
