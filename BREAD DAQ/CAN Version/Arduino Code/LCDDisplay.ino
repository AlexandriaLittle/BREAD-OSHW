/*
* Writes label of what sensor is being used to the LCD screen
*/
void changeLabel(){
  lcd.clear();
  delay(750);
  lcd.setCursor(0,0);

  char temp[2];
  sprintf(temp,"%d:",curChannel);

  lcd.print(temp);

  switch(sensorType[curChannel]){
    case THERMOCOUPLE_K:
      lcd.print(F("K Thermocouple"));
      output[curChannel] = CELSIUS;
      break;
    case CURRENT:
      lcd.print(F("Current Clamp"));
      output[curChannel] = AMPS;
      break;
    case PHOTORESISTOR:
      lcd.print(F("Photoresistor"));
      output[curChannel] = LUX;
      break;
    default:
      SPI.end();
      return;
      break;
  }
  delay(750);
}

/*
* Writes formatted data to the bottom row of the LCD screen
*/
void displayData(float data){
  char display[16];
  char dataStr[7];

  floatToStr(data,dataStr);

  
  switch(output[curChannel]){
    case CELSIUS:
      sprintf(display,"%s %cC        ",dataStr,(char) 223);
      break;
    case FAHRENHEIT:
      sprintf(display,"%s %cF        ",dataStr,(char) 223);
      break;
    case MILLIAMPS:
      sprintf(display,"%s mA        ",dataStr);
      break;
    case AMPS:
      sprintf(display,"%s  A        ",dataStr);
      break;
    case LUX:
      sprintf(display,"%s lux        ",dataStr);
      break;
    default:
      SPI.end();
      return;
      break;
  }

  //Serial.print(display);

  //Write data to the display, make sure to keep any units currently in use
  lcd.setCursor(0,1);
  lcd.print(display);
  //delay(750);
}

void floatToStr(float input, char* str){
  int start = (int) input;
  int end = (int) (input * 1000) - (start*1000);
  sprintf(str,"%3d.%03d",start,end);
  //Serial.print(str);
}
