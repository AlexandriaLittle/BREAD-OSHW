#include <Wire.h>
//#include <SPI.h>

#define I2C_ADR 5 //Set this however you want

#define DIR1  7
#define MC1   9
#define BR1   6

bool dir1 = 1;
bool br1 = 0;

int pwm1;

typedef union //Define a float that can be broken up and sent via I2C
{
 float number;
 uint8_t bytes[4];
} FLOATUNION_t;

FLOATUNION_t RX;

byte commandSelect[3];
int8_t speedSelect;
int8_t motor1Speed;
byte motorSelect;
bool changeParam = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(MC1, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(BR1, OUTPUT);

  Serial.begin(9600);
  Wire.begin(I2C_ADR);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  if(changeParam){
    if(speedSelect == 0){
      br1 = 1;
      pwm1 = 0;
      Serial.println("Motor 1 brake");
    }
    else if(speedSelect < 0 && speedSelect >= -100){
      br1 = 0;
      dir1 = 0;
      speedSelect *= -1;
      pwm1 = map(speedSelect, 0, 100, 0, 255);
      Serial.print("Motor 1 back ");
      Serial.println(pwm1);
    }
    else if(speedSelect > 0 && speedSelect <= 100){
      br1 = 0;
      dir1 = 1;
      pwm1 = map(speedSelect, 0, 100, 0, 255);
      Serial.print("Motor 1 forward ");
      Serial.println(pwm1);
    }
    else{
      Serial.println("Invalid Entry, nothing will be changed");
    }
        
    digitalWrite(DIR1, dir1);
    analogWrite(MC1, pwm1);

    changeParam = false;
  }
}

void requestEvent() {
  Serial.print("Sending: ");
  Serial.print(motor1Speed);

  Wire.write(motor1Speed);
}

void receiveEvent(int howMany) {
  int i=0;
  while (Wire.available()) {
    commandSelect[i] = Wire.read();
    Serial.print(i);
    Serial.print("-> ");
    Serial.print(commandSelect[i]);
    Serial.print(", ");
    i++;
  }
  Serial.println();
  motorSelect = commandSelect[0];
  speedSelect = commandSelect[1];
  
  changeParam = true;
}
