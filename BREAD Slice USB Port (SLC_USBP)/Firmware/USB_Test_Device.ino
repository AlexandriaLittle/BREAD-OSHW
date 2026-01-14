bool received = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available() && received){
    received = false;
    char rec = (char)Serial.read();
    if(rec == 'r'){
      digitalWrite(LED_BUILTIN, HIGH);
    }
//    Serial.println('r');
  }
}
