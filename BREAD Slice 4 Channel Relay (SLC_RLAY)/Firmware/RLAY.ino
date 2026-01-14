/*
 * This code turns each relay on and off every 2 seconds and is intended for testing purposes
 * Voltage input can be read by first tuning the potentiometer to a reference voltage
 */

int pin1 = 6;
int pin2 = 9;
int pin3 = 10;
int pin4 = 11;

float referenceVoltage = 11.9;

void setup() {
  // put your setup code here, to run once:
  initialize(8);
  Serial.begin(9600);
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);
  Serial.println("HIGH");
  delay(2000);
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  Serial.println("LOW");
  delay(2000);

  //read voltage input
  float val0 = float(analogRead(A0))*referenceVoltage/1023;
  float val1 = float(analogRead(A1))*referenceVoltage/1023;
  float val2 = float(analogRead(A2))*referenceVoltage/1023;
  float val3 = float(analogRead(A3))*referenceVoltage/1023;
  Serial.print(val0);
  Serial.print(",");
  Serial.print(val1);
  Serial.print(",");
  Serial.print(val2);
  Serial.print(",");
  Serial.println(val3);
}
