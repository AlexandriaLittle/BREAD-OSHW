#ifndef BREAD_DAQ_H
#define BREAD_DAQ_H

#include <SPI.h>
#include <LiquidCrystal.h>
#include <Math.h>
#include <String.h>
#include <SD.h> //For SD
#include <DS3231.h> //For RTC
#include <Wire.h> //For RTC
#include "myAD7193.h"

#define ANALOG_PIN        A0        //Analog pin to read voltage from
#define SD_CS             10        //Sets chip select for the SD card
#define AD7193_CS         9         //Pin for AD7193
#define SW1pin            A1        //Pin for button 1
#define SW2pin            A2        //Pin for button 2
#define ARDUINO_VOLTAGE   5.0         //Max voltage on the Arduino
#define NUM_LEVELS        1024      //Resolution of analogRead
#define VOLTAGE_PER_LEVEL ARDUINO_VOLTAGE/NUM_LEVELS
#define NUM_CHANNELS      6


//Manual enumerations to make list cycling possible while still using readable names. 
//When adding new sensors or outputs, add to the start of the list with an increased number
//Outputs have two digits due to these being used in case statements, meaning they all need to be different
//---------------SENSORS----------------------
#define THERMOCOUPLE_K 3
#define CURRENT 2
#define PHOTORESISTOR 1
#define NULL_S 0

//---------------OUTPUTS----------------------
#define CELSIUS 12
#define FAHRENHEIT 11
#define NULL_T 10
#define AMPS 22
#define MILLIAMPS 21
#define NULL_C 20
#define LUX 31
#define NULL_P 30

//enum sensorTypes {THERMOCOUPLE_K,CURRENT,PHOTORESISTOR,NULL_S};
//enum outputTypes {CELSIUS,FAHRENHEIT,NULL_T,AMPS,MILLIAMPS,NULL_C,LUX,NULL_P};

void AD7193_setup();

void SDsetup();
void SDwrite(float data);

void changeLabel();
void displayData(float data);
void floatToStr(float input, char* str);

float readSensor(int channelNumber);

float thermocoupleKOutput();
float Thermocouple_Ktype_VoltageToTempDegC(float voltage);
float Thermocouple_Ktype_TempToVoltageDegC(float temperature);
float power_series(int n, float input, float coef[]);

//float currentOutput();

float photoresistorOutput(int terminal);

#endif