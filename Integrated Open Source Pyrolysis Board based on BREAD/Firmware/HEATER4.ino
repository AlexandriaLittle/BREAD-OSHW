#include <Wire.h>
#include "max6675.h"

#define PWM1  7

#define SS1   10
#define SS2   11
#define DATA1 12
#define CLK1  13

#define I2C_ADR 4 //Set this however you want

#define MAX_DUTY_CYCLE  10  // to prevent PID control from overheating coils (increase for slower heating systems)

// initialize the Thermocouples
MAX6675 CH1(CLK1, SS1, DATA1);
MAX6675 CH2(CLK1, SS2, DATA1);


typedef union //Define a float that can be broken up and sent via I2C
{
  float number;
  uint8_t bytes[4];
} FLOATUNION_t;

FLOATUNION_t RX;

byte commandSelect[3];
byte tempSelect = 0;  // select thermocouple to measure
float dutySelect = 0;  // select duty cycle for heater

int onTime1;
int offTime1;

int period = 1000; // duty cycle period in milliseconds

bool heater1On = false;

long curTime1 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(PWM1, OUTPUT);

  Wire.begin(I2C_ADR);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

  // wait for MAX chip to stabilize
  delay(500);
  
  curTime1 = millis();
  
  onTime1 = period*dutySelect/100;  
  offTime1 = period-onTime1;
}

void loop() {
  // put your main code here, to run repeatedly:

    if(dutySelect != 0){  // only run if duty cycle is nonzero
      onTime1 = period*dutySelect/100;
      offTime1 = period-onTime1;
      if(!heater1On && millis() - curTime1 >= offTime1){  //wait for off cycle to finish
        curTime1 = millis();
        digitalWrite(PWM1, HIGH);  //turn on
        Serial.println("1 -> ON");
        heater1On = true;
      }
      else if(heater1On && millis() - curTime1 >= onTime1){ //wait for on cycle to finish
        curTime1 = millis();
        digitalWrite(PWM1, LOW);   //turn off
        Serial.println("1 -> OFF");
        heater1On = false;
      }
    }
    else if (heater1On){
        heater1On = false;
        digitalWrite(PWM1, LOW);   //turn off
        Serial.println("1 -> OFF");
    }
}

void requestEvent() {
  switch (tempSelect) {
    case 1:
      RX.number = CH1.readCelsius();  // reference a pointer instead
      break;
    case 2:
      RX.number = CH2.readCelsius();
      break;
    default:
      RX.number = 0;
  }
  if(!isnan(RX.number)){
    for (int i = 0; i <= 3; i++)
    {
      Wire.write(RX.bytes[i]);
      Serial.print(RX.bytes[i]);
      Serial.print(", ");
    }
    Serial.println("-> Float: ");
    Serial.println(RX.number);
  }
  else{
    for (int i = 0; i <= 3; i++)
    {
      Wire.write(0);
      Serial.print(0);
      Serial.print(", ");
    }
    Serial.println();
  }
  commandSelect[1] = 0;
}

void receiveEvent(int howMany) {
  int i=0;
  while (Wire.available()) {
    commandSelect[i] = Wire.read();
    Serial.print(commandSelect[i]);
    Serial.print(", ");
    i++;
  }
  Serial.println();
  
  switch(commandSelect[0]){
    case 'T':
      tempSelect = commandSelect[1];  // wants temperature readings
      break;
    case 1:
      dutySelect = commandSelect[1];  // wants to change duty cycle of heater
      tempSelect = 0;
      break;
  }
  if(dutySelect > MAX_DUTY_CYCLE){
    dutySelect = MAX_DUTY_CYCLE;
  }
}
