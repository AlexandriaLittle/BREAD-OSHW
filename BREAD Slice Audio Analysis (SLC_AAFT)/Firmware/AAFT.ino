#include <Wire.h>
#include <arduinoFFT.h> //import the library
#define SAMPLES 128 //Must be a power of 2
#define SAMPLING_FREQUENCY 10000 //Hz (1k?)
arduinoFFT FFT = arduinoFFT(); // create FFT object
unsigned int sampling_period_us; unsigned long microseconds;
double vReal[SAMPLES]; //Real part of FFT array
double vImag[SAMPLES]; //Imaginary part of FFT array
double data;
int addr = 8;         // Slave address 

typedef union //Define a float that can be broken up and sent via I2C
{
 float number;
 uint8_t bytes[4];
} FLOATUNION_t;

FLOATUNION_t RX_P1;
FLOATUNION_t RX_P2;
FLOATUNION_t RX_P3;
FLOATUNION_t RX_P4;

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  
  sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));
  Wire.begin(I2C_ADR);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event

  inputString.reserve(50);
  
  Serial.begin(115200);

  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc

}

void loop() {
   /*SAMPLING*/
   for(int i=0; i<SAMPLES; i++)
   {
       microseconds = micros();    //Overflows after around 70 minutes!
    
       vReal[i] = analogRead(A0); //Full Spectrum Line. We can do different segments later.
       vImag[i] = 0;
    
       while(micros() < (microseconds + sampling_period_us)){
       }
   }

   /*FFT*/                                                                // builtin FFT library and methods
   FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
   FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
   FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
   double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

   /*PRINT RESULTS*/
   Serial.println(peak);                                         //Print out what frequency is the most dominant.

   for(int i=0; i<(SAMPLES/2); i++)
   {
       /*View all these three lines in serial terminal to see which frequencies has which amplitudes*/
        
       //Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
       //Serial.println(" ");
       Serial.println(vReal[i], 1);    //View only this line in serial plotter to visualize the bins
   }

   if (stringComplete) {
    // clear the string:
    inputString = "";
    stringComplete = false;
   }

   delay(1000);  //Repeat the process every second OR:
   //while(1);       //Run code once

}

void requestEvent() {
  for(int i=0; i<(SAMPLES/2); i++)
   {
       data = vReal[i];
       Wire.write((byte)data);    //View only this line in serial plotter to visualize the bins
   }
}
