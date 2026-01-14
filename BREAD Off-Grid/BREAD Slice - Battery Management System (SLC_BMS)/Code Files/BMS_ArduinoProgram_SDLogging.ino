#include <Wire.h>

int CHG_EN = 9; // active low
int CHGIN_ = 5; // active low
int PGOOD_ = 6; // active low
int CHGI = 7;   // CHG status LED
int PGOODI = 8; // Power good status LED
int ISET = A0;  // Used to monitor charging current
int BatV = A1;  // Future pin to read battery voltage.

int CHG_Status;
int POWER_Status;
int CHGV_Status;
int CHGI_Status;
int R_ISET = 1000;
int BatV_Status;

void setup() {
  //LOAF communication setup.
  Wire.begin(10);                 // join i2c bus with address #10
  Wire.onRequest(requestVoltage); // register event

  //Pin setup.
  pinMode(CHGIN_, INPUT_PULLUP);
  pinMode(PGOOD_, INPUT_PULLUP);
  pinMode(CHGI, OUTPUT);
  pinMode(PGOODI, OUTPUT);
  pinMode(CHG_EN, OUTPUT);

  //Sets charge enable pin to active.
  digitalWrite(CHG_EN,LOW);

  Serial.begin(9600);
}

void loop() {
  // update status LEDs.
  CHG_Status = !digitalRead(CHGIN_);
  POWER_Status = !digitalRead(PGOOD_);

  digitalWrite(CHGI, CHG_Status);
  digitalWrite(PGOODI, POWER_Status);

  // read and calculate charge current
  // This section uses the formula provided in the BQ24074 datasheet
  // and has not been proven to be functional

  //Rread Battery Voltage.
  BatV_Status = analogRead(BatV);
  // Read ISET
  CHGV_Status = analogRead(ISET);
  //CHGV_Status*1000;
  // Map read value to mV in order to avoid the need for decimals
  CHGV_Status = map(CHGV_Status, 0, 1023, 0, 5000);
  CHGI_Status = CHGV_Status * 400 / R_ISET;

  //Prints to help troubleshooting.
  Serial.print("CHG I: ");
  Serial.println(CHGI_Status);
  Serial.print("CHG V: ");
  Serial.println(CHGV_Status);
  Serial.print("Battery VOltage: ");
  Serial.println(BatV_Status);

  delay(200); // no need to update stuff more than 5x per second
}

// request code for SD & LOAF communication.
void requestVoltage(){
  char string[16];
  sprintf(string, "%d", CHGV_Status);
  Serial.println(string);
  Wire.write(string);
}