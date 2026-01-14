#include <Wire.h>
#define I2C_ADR 7

typedef union //Define a float that can be broken up and sent via I2C
{
 float number;
 uint8_t bytes[4];
} FLOATUNION_t;

FLOATUNION_t RX_P1;
FLOATUNION_t RX_P2;

#include <PID_v1.h>
#include <SPI.h>

#define PIN_OUTPUT 6 //Change these
#define PIN_INPUT 7

//Define Variables we'll be connecting to
double Setpoint, Input, Output;
double Ramprate,Target,Setpoint_O;
boolean Rising; //1 Means temp rising


String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

//Specify the links and initial tuning parameters
// Tune these a bit more precisely later
double Kp=50, Ki=1, Kd=.5;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


void setup() {
  // put your setup code here, to run once:
  Wire.begin(I2C_ADR);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event

  //initialize the variables we're linked to
  Input = analogRead(PIN_INPUT);
  Setpoint = 0;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);

  inputString.reserve(50);

    Serial.begin(115200);
 
  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc
  delay(500);

}

void loop() {
  static unsigned long lastRefreshTime = 0;
  Input = analogRead(PIN_INPUT);
  if(millis() - lastRefreshTime >= 1000)
  {
    if (Setpoint != Target)
    {
      double Step = Ramprate/60;
      if (Rising)
      {
        Setpoint+=Step;
        if (Setpoint > Target)
          Setpoint = Target;
      }
      else
      {
        Setpoint-=Step;
        if (Setpoint < Target)
          Setpoint = Target;
      }
    }
     Serial.print(Setpoint); 
     Serial.print(",");
     Serial.print(Target); 
     Serial.print(",");
     Serial.print(Input);
     Serial.print(",");
     Serial.println(Output*100/255);
    
    lastRefreshTime += 1000;
  }
  
  //ADD A SAFETY FUNCTION
  myPID.Compute();
  analogWrite(PIN_OUTPUT, Output);

    if (stringComplete) {
    // clear the string:
    inputString = "";
    stringComplete = false;
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
      Target = inputString.substring(0, inputString.indexOf(',')).toDouble();
      Ramprate = inputString.substring(inputString.indexOf(',')+1).toDouble();
      if (Target >= Setpoint)
        Rising = 1;
      if (Target < Setpoint)
        Rising = 0;
    }
  }
}








// SYSTEM COMMS

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  RX_P1.number = 0; RX_P2.number = 0;
  int ByteCount = 0;
  while (1 <= Wire.available()) { // loop through all but the last
    if (ByteCount <= 3)
    {
      RX_P1.bytes[ByteCount] = Wire.read(); // receive a byte as character
    }
    else
    {
      RX_P2.bytes[ByteCount-4] = Wire.read(); // receive a byte as character
    }
    ByteCount++;
  }
  stringComplete = true;
  Target = RX_P1.number;
  Ramprate = RX_P2.number;
  if (Target >= Setpoint)
    Rising = 1;
  if (Target < Setpoint)
    Rising = 0;

  digitalWrite(8,HIGH);
}

void requestEvent() {
  RX_P1.number = Input;
  RX_P2.number = Setpoint;
  //Send both parameters
  for (int i = 0; i <=3; i++)
  {
    Wire.write(RX_P1.bytes[i]);
        //Serial.println(RX_P1.bytes[i]);
  }
  for (int i = 0; i <=3; i++)
  {
    Wire.write(RX_P2.bytes[i]);
    //Serial.println(RX_P2.bytes[i]);
  }
  digitalWrite(8,LOW);
}
