#include <Wire.h>
#include <SPI.h>
#include <SD.h>

File myFile;
int i = 1;  // int for indexing SD file name.
String filename;

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  //Creating filename string for log file naming.
  filename = "BREAD/log_";
  filename = filename + i;
  filename = filename + ".txt";

  //Chekcing if SD card is available. IF so checks for BREAD directory and creates on if it does not exist.
  if (SD.begin(8) == 1) {
    Serial.println("SD connected sucessfuly...");
    if (SD.exists("BREAD/") != 1) {
      Serial.println("making directory...");
      SD.mkdir("BREAD");
    }
    Serial.println("Creating file...");
    //Increments filename so a new log is created when arduino is reset.
    if (SD.exists(String(filename)) == 1) {
      while (SD.exists(String(filename)) == 1) {
        i++;
        filename = "BREAD/log_";
        filename = filename + i;
        filename = filename + ".txt";
      }
    } else {
      filename = "BREAD/log_1.txt";
    }
  } else {
    Serial.println("SD failed to connect...");
  }
}

void loop() {
  myFile = SD.open(filename, FILE_WRITE);
  myFile.print("Charging voltage: ");
  Wire.requestFrom(10, 16);   // request 16 bytes from peripheral device #10
  while (Wire.available()) {  // peripheral may send less than requested
    char c = Wire.read();     // receive a byte as character
    if (c > 0 && c < 58)      // Checking if data is blank and only printing if it is not.
    {
      //prints recieved data
      myFile.print(c);
      Serial.print(c);
    }
  }
  myFile.println(" mV");  // Prints label for data
  Serial.println();
  myFile.close();  // Necessary to save information written to file.
  delay(1000);
}