#include <Wire.h>
#include <SPI.h>
#include <arduinoFFT.h> //import the fft library
#define SAMPLES 64 //Must be a power of 2
#define SAMPLING_FREQUENCY 9600 //Hz (1k?) //Was 10000
arduinoFFT FFT = arduinoFFT(); // create FFT object
unsigned int sampling_period_us; unsigned long microseconds;
double vReal[SAMPLES]; //Real part of FFT array
double vImag[SAMPLES]; //Imaginary part of FFT array
double data;
int mode;

#define I2C_ADR 23 //Set this however you want

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
FLOATUNION_t RX_P5;
FLOATUNION_t RX_P6;

int Command, arg1, arg2, arg3, arg4, arg5, arg6;

// Class for defining and using analog channels
class Channel {
  private:
      byte pin;
      double samples[16];
  public:
      Channel(byte pin){
        this->pin = pin;
        init();
      }  
      int EN; 
      void init(){
        pinMode(pin, INPUT);
      }
      void sample(){
        if(EN){
          for(int i=0; i<16; i++){ //Arbitrarily choose an amount of samples up to 16
            samples[i] = analogRead(pin);
          }
        }
      }
      void disp(){
        if(EN){
          for(int i=0; i<16; i++){ //Print the same amount of samples
            Serial.println(samples[i]);
          }
        }
      }
      void freq(){
        for(int i=0; i<SAMPLES; i++){
          microseconds = micros();    //Overflows after around 70 minutes!
    
          vReal[i] = analogRead(pin); //Full Spectrum Line. We can do different segments later.
          vImag[i] = 0;
    
          while(micros() < (microseconds + sampling_period_us)){}
        }
        
        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
        double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

        /*PRINT RESULTS*/
        Serial.println(peak); //Uncomment for Peak Frequency

        for(int i=2; i<(SAMPLES/2); i++)
        {
          /*View these three lines in serial terminal to see which frequencies have which amplitudes*/
          //Serial.print((i * 1.0 * SAMPLING_FREQUENCY) / SAMPLES, 1);
          //Serial.print(", ");
          //Serial.println(vReal[i], 1);    //View only this line in serial plotter to visualize the bins
        }
      }
};

Channel CH0(A0); 
Channel CH1(A1); 
Channel CH2(A2); 
Channel CH3(A3); 
Channel CH4(A6); 
Channel CH5(A7); 

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  Wire.begin(I2C_ADR);            // join i2c bus with address #8
  //Wire.onReceive(receiveEvent);   // register event
  //Wire.onRequest(requestEvent);   // register event

  sampling_period_us = round(1000000*(1.0/SAMPLING_FREQUENCY));

  // Init all channels as not enabled
  
  CH0.EN = 1;
  CH1.EN = 0;
  CH2.EN = 0;
  CH3.EN = 0;
  CH4.EN = 0;
  CH5.EN = 0;
  
  inputString.reserve(50);

  Serial.begin(115200);

  while (!Serial) delay(1); // wait for Serial on Leonardo/Zero, etc
  delay(500);
}

void loop() {

  switch(mode){
    case 1: //Config
      break;
    case 2: //Time Domain
      if(CH0.EN){CH0.sample(); CH0.disp();}
      if(CH1.EN){CH1.sample(); CH1.disp();}
      if(CH2.EN){CH2.sample(); CH2.disp();}
      if(CH3.EN){CH3.sample(); CH3.disp();}
      if(CH4.EN){CH4.sample(); CH4.disp();}
      if(CH5.EN){CH5.sample(); CH5.disp();}
      break;
    case 3: //Freq Domain
      if(CH0.EN){CH0.freq();}
      if(CH1.EN){CH1.freq();}
      if(CH2.EN){CH2.freq();}
      if(CH3.EN){CH3.freq();}
      if(CH4.EN){CH4.freq();}
      if(CH5.EN){CH5.freq();}
      break;
    default://None
      break;
  }
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


      int result = sscanf(inputString.c_str(), "%d,%d,%d,%d,%d,%d,%d", &Command, &arg1, &arg2, &arg3, &arg4, &arg5, &arg6);

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
      Serial.print(arg5);
      Serial.print(", ");
      Serial.println(arg6);

      switch(Command){
        case 0:
          //standard comms configuration command
          break;

        case 1:
          
          CH0.EN = arg1;
          CH1.EN = arg2;
          CH2.EN = arg3;
          CH3.EN = arg4;
          CH4.EN = arg5;
          CH5.EN = arg6;
          
          break;
          
        case 2:
          mode = arg1;
      }
      
    }
  }
}
