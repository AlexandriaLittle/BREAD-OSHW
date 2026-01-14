#include <Wire.h>
#include "max6675.h"

#define PWM1  5
#define PWM2  6
#define PWM3  7

#define SS1   9
#define SS2   10
#define SS3   11
#define DATA1 12
#define CLK1  13

#define I2C_ADR 1 //Set this however you want

#define MAX_DUTY_CYCLE  10  // to prevent PID control from overheating coils (increase for slower heating systems)

// initialize the Thermocouples
MAX6675 CH1(CLK1, SS1, DATA1);
MAX6675 CH2(CLK1, SS2, DATA1);
MAX6675 CH3(CLK1, SS3, DATA1);


typedef union //Define a float that can be broken up and sent via I2C
{
  float number;
  uint8_t bytes[4];
} FLOATUNION_t;

FLOATUNION_t RX;

byte commandSelect[3];
byte tempSelect = 0;  // select thermocouple to measure
byte heaterSelect = 0;  // select heater to control
float dutySelect1 = 0;  // select duty cycle for heater1
float dutySelect2 = 0;  // select duty cycle for heater2
float dutySelect3 = 0;  // select duty cycle for heater3

int onTime1;
int offTime1;

int onTime2;
int offTime2;

int onTime3;
int offTime3;

int period = 1000; // duty cycle period in milliseconds

bool heater1On = false;
bool heater2On = false;
bool heater3On = false;

long curTime1 = 0;
long curTime2 = 0;
long curTime3 = 0;

long lastUpdate = 0;
long updateInterval = 1000;  // in milliseconds

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(PWM3, OUTPUT);

  Wire.begin(I2C_ADR);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

  // wait for MAX chip to stabilize
  delay(500);
  
  curTime1 = millis();
  curTime2 = millis();
  curTime3 = millis();
  
  onTime1 = period*dutySelect1/100;
  onTime2 = period*dutySelect2/100;
  onTime3 = period*dutySelect3/100;
  
  offTime1 = period-onTime1;
  offTime2 = period-onTime2;
  offTime3 = period-onTime3;
}

void loop() {
  // put your main code here, to run repeatedly:

    // Heater 1 --------------------------------------------------------
    if(dutySelect1 != 0){  // only run if duty cycle is nonzero
      onTime1 = period*dutySelect1/100;
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
      
    // Heater 2 --------------------------------------------------------
    if(dutySelect2 != 0){  // only run if duty cycle is nonzero
      onTime2 = period*dutySelect2/100;
      offTime2 = period-onTime2;
      if(!heater2On && millis() - curTime2 >= offTime2){  //wait for off cycle to finish
        curTime2 = millis();
        digitalWrite(PWM2, HIGH);  //turn on
        Serial.println("2 -> ON");
        heater2On = true;
      }
      else if(heater2On && millis() - curTime2 >= onTime2){ //wait for on cycle to finish
        curTime2 = millis();
        digitalWrite(PWM2, LOW);   //turn off
        Serial.println("2 -> OFF");
        heater2On = false;
      }
    }
    else if (heater2On){
        heater2On = false;
        digitalWrite(PWM2, LOW);   //turn off
        Serial.println("2 -> OFF");
    }
      
    // Heater 3 --------------------------------------------------------
    if(dutySelect3 != 0){  // only run if duty cycle is nonzero
      onTime3 = period*dutySelect3/100;
      offTime3 = period-onTime3;
      if(!heater3On && millis() - curTime3 >= offTime3){  //wait for off cycle to finish
        curTime3 = millis();
        digitalWrite(PWM3, HIGH);  //turn on
        Serial.println("3 -> ON");
        heater3On = true;
      }
      else if(heater3On && millis() - curTime3 >= onTime3){ //wait for on cycle to finish
        curTime3 = millis();
        digitalWrite(PWM3, LOW);   //turn off
        Serial.println("3 -> OFF");
        heater3On = false;
      }
    }
    else if (heater3On){
        heater3On = false;
        digitalWrite(PWM3, LOW);   //turn off
        Serial.println("3 -> OFF");
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
    case 3:
      RX.number = CH3.readCelsius();
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
    Serial.print("-> Float: ");
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
      dutySelect1 = commandSelect[1];  // select heater to change duty cycle
      tempSelect = 0;
      break;
    case 2:
      dutySelect2 = commandSelect[1];  // select heater to change duty cycle
      tempSelect = 0;
      break;
    case 3:
      dutySelect3 = commandSelect[1];  // select heater to change duty cycle
      tempSelect = 0;
      break;
  }
  if(dutySelect1 > MAX_DUTY_CYCLE){
    dutySelect1 = MAX_DUTY_CYCLE;
  }
  if(dutySelect2 > MAX_DUTY_CYCLE){
    dutySelect2 = MAX_DUTY_CYCLE;
  }
  if(dutySelect3 > MAX_DUTY_CYCLE){
    dutySelect3 = MAX_DUTY_CYCLE;
  }
}
