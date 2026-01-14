int CHGIN_ = 5; // active low
int PGOOD_ = 6;  // active low
int CHGI = 7;    // CHG status LED
int PGOODI = 8;  // Power good status LED
int ISET = A0;   // Used to monitor charging current

int CHG_Status;
int POWER_Status;
int CHGV_Status;
int CHGI_Status;
int R_ISET = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(CHGIN_, INPUT_PULLUP);
  pinMode(PGOOD_, INPUT_PULLUP);
  pinMode(CHGI, OUTPUT);
  pinMode(PGOODI, OUTPUT);

  Serial.begin(9600);
  Serial.println("Charging Current (VISET) in mA");
}

void loop() {
  // put your main code here, to run repeatedly:

  // update status LEDs
  CHG_Status = !digitalRead(CHGIN_);
  POWER_Status = !digitalRead(PGOOD_);
  //Serial.print("%d, %d\n", CHGIN_)
  digitalWrite(CHGI, CHG_Status);
  digitalWrite(PGOODI, POWER_Status);


  // read and calculate charge current
  // This section uses the formula provided in the BQ24074 datasheet
  // and has not been proven to be functional

  // Read ISET
  CHGV_Status = analogRead(ISET);
  // Map read value to mV in order to avoid the need for decimals
  CHGV_Status = map(CHGV_Status, 0, 1023, 0, 5000);
  CHGI_Status = CHGV_Status * 400 / R_ISET;

  Serial.println(CHGI_Status);
  delay(200); // no need to update stuff more than 5x per second
}
