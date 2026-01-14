#include <SPI.h>

int i;
String str;

void setup() {
  Serial.begin(9600); //initialize serial
  //while(!Serial); //wait for serial to connect
  pinMode(MISO, OUTPUT); //initialize spi in slave mode
  SPCR |= _BV(SPE);

  //initial values
  i = 0;
  str = "\0";
}

void loop () {
  
  //SPIF indicates transmission complete (byte received)
  if ((SPSR & (1 << SPIF)) != 0) {
    
    if(Serial.available() > 0) {
      //I added a space here as a workaround
      //The system wasn't reading the first character otherwise
      str = " " + Serial.readString();
    }
    
    //when the end of the string has been reached, reset the counter and the string
    if(i >= str.length()) {
      i = 0;
      str = "\0";
    }

    //get the next character
    int out_val = str[i];

    //increment the counter
    i++;
    
    //echo character to serial monitor
    Serial.println(out_val);

    //send the character via SPI
    SPDR = out_val;
  }
}
