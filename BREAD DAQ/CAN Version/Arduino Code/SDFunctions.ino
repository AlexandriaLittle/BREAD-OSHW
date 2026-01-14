//Called once in setup, moved here for brevity
void SDsetup(){
  //RTC setup (pass corect datetime info)
  if (setTime == 1){
    setRTC.setMinute(0);
    setRTC.setMonth(0);
    setRTC.setHour(0);
    setRTC.setDate(0);
    setRTC.setYear(24);
  }

  // Handle SD file creation and display status to lcd
  if (SD.begin(SD_CS) == 1) {
    lcd.setCursor(0,0);
    lcd.print(F("SD connected sucessfuly..."));
    delay(750);
    if (SD.exists("BREAD/") != 1) {
      lcd.setCursor(0,0);
      lcd.print(F("making directory..."));
      delay(750);
      SD.mkdir("BREAD");
    }
    lcd.setCursor(0,0);
    lcd.print(F("Creating file..."));
    delay(750);
    //Increments filename so a new log is created when arduino is reset.
    filename = "BREAD/log_01.txt";

    uint8_t i = 0;
    if (SD.exists(filename) == 1) {
      while (SD.exists(filename) == 1) {
        i++;
        sprintf(filename,"BREAD/log_%02d.txt",i);
      }
    } 
    else {
      filename = "BREAD/log_01.txt";
    }
    dataFile = SD.open(filename, FILE_WRITE);
    dataFile.close();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("File Created"));
    delay(750);
    //lcd.clear();
    SDconn = 1;
  }
  else {
    lcd.setCursor(0,0);
    lcd.print(F("SD failed to connect..."));
    delay(2000);
  }

  dataFile = SD.open(filename, FILE_WRITE);
  delay(1000);
}

void SDwrite(float data,uint32_t channel){
  if (SDconn == 1){
    DateTime now = myRTC.now();

    //char printStr[50];
    char dataStr[7];
    char* outputStr;
    floatToStr(data,dataStr);

    switch(output[channel]){
    case CELSIUS:
      outputStr = "C";
      break;
    case FAHRENHEIT:
      outputStr = "F";
      break;
    case MILLIAMPS:
      //sprintf(outputStr,"mA  ");
      outputStr = "mA";
      break;
    case AMPS:
      //sprintf(outputStr,"A   ");
      outputStr = "A";
      break;
    case LUX:
      //sprintf(outputStr,"lux ");
      outputStr = "lux";
      break;
    default:
      SPI.end();
      return;
      break;
    }

    //sprintf(printStr,"%d/%d/%d %d:%d:%d %s %s\n",now.year(),now.month(),now.day(),now.hour(),now.minute(),now.second(),dataStr,outputStr);
    //dataFile.print(printStr);
    //dataFile.close();

    //delay(500);

    
    //dataFile = SD.open(filename, FILE_WRITE);
    //DateTime now = myRTC.now();
    //lcd.setCursor(0,0);
    //lcd.print(F("running..."));
    dataFile.print(now.year(), DEC);
    dataFile.print('/');
    dataFile.print(now.month(), DEC);
    dataFile.print('/');
    dataFile.print(now.day(), DEC);
    dataFile.print(' ');
    dataFile.print(now.hour(), DEC);
    dataFile.print(':');
    dataFile.print(now.minute(), DEC);
    dataFile.print(':');
    dataFile.print(now.second(), DEC);
    dataFile.print(' ');
    dataFile.print(channel,DEC);
    dataFile.print(' ');
    dataFile.print(dataStr);
    dataFile.print(' ');
    dataFile.println(outputStr);
    dataFile.flush();
    //delay(500);
  }
}

void SDwriteCANDAQ(char* data){
  if (SDconn == 1){
    DateTime now = myRTC.now();

    float* dataFlt = (float*) &(data[3]); //Get float info from data
    //char printStr[50];
    char dataStr[7];
    char* outputStr;
    floatToStr(*dataFlt,dataStr); //Convert float to a printable String

    switch((uint8_t) data[2]){
    case CELSIUS:
      outputStr = "C";
      break;
    case FAHRENHEIT:
      outputStr = "F";
      break;
    case MILLIAMPS:
      //sprintf(outputStr,"mA  ");
      outputStr = "mA";
      break;
    case AMPS:
      //sprintf(outputStr,"A   ");
      outputStr = "A";
      break;
    case LUX:
      //sprintf(outputStr,"lux ");
      outputStr = "lux";
      break;
    default:
      SPI.end();
      return;
      break;
    }

    //sprintf(printStr,"%d/%d/%d %d:%d:%d %s %s\n",now.year(),now.month(),now.day(),now.hour(),now.minute(),now.second(),dataStr,outputStr);
    //dataFile.print(printStr);
    //dataFile.close();

    //delay(500);

    
    //dataFile = SD.open(filename, FILE_WRITE);
    //DateTime now = myRTC.now();
    //lcd.setCursor(0,0);
    //lcd.print(F("running..."));
    dataFile.print(now.year(), DEC);
    dataFile.print('/');
    dataFile.print(now.month(), DEC);
    dataFile.print('/');
    dataFile.print(now.day(), DEC);
    dataFile.print(' ');
    dataFile.print(now.hour(), DEC);
    dataFile.print(':');
    dataFile.print(now.minute(), DEC);
    dataFile.print(':');
    dataFile.print(now.second(), DEC);
    dataFile.print(' External ');
    dataFile.print((uint8_t) data[1],DEC);
    dataFile.print(' ');
    dataFile.print(dataStr);
    dataFile.print(' ');
    dataFile.println(outputStr);
    dataFile.flush();
    //delay(500);
  }
}

void SDwriteVision(unsigned char len, unsigned char buf[]){
  DateTime now = myRTC.now();
  delay(100);
  dataFile.print(now.year(), DEC);
  dataFile.print('/');
  dataFile.print(now.month(), DEC);
  dataFile.print('/');
  dataFile.print(now.day(), DEC);
  dataFile.print(' ');
  dataFile.print(now.hour(), DEC);
  dataFile.print(':');
  dataFile.print(now.minute(), DEC);
  dataFile.print(':');
  dataFile.print(now.second(), DEC);
  dataFile.print(' ');
  dataFile.print("Vision");
  for (int i = 0; i < len; i++) { // print the data
    dataFile.print(' ');
    unsigned char analysisType = buf[i] >> 1;
    bool result = buf[i] & 0x1;
    switch (analysisType) {
      case COLOR_INTEGRATION:
        dataFile.print("CD: ");
        break;
      case OBJECT_DETECTION:
        dataFile.print("OD: ");
        break;
      case SPECTROMETER:
        dataFile.print("Spec: ");
        break;
    }
    if(result){
      dataFile.print("True");
    }
    else{
      dataFile.print("False");
    }
  }
  dataFile.println();
  dataFile.flush();
}