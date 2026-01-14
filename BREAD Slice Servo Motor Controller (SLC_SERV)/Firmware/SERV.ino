/*
 * Currently intended for testing. Code wipes each servo through 180 degrees and back
 */

#include <Servo.h>

#define serv1Pin 5
#define serv2Pin 6
#define serv3Pin 9
#define serv4Pin 10
#define serv5Pin 11

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

void setup() {
  // put your setup code here, to run once:

  servo1.attach(serv1Pin);
  servo2.attach(serv2Pin);
  servo3.attach(serv3Pin);
  servo4.attach(serv4Pin);
  servo5.attach(serv5Pin);
  
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  servo5.write(0);
  
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:

  for(int i=0; i<=180; i++){
    servo1.write(i);
    servo2.write(i);
    servo3.write(i);
    servo4.write(i);
    servo5.write(i);
    delay(5);
  }
  for(int i=180; i>=0; i--){
    servo1.write(i);
    servo2.write(i);
    servo3.write(i);
    servo4.write(i);
    servo5.write(i);
    delay(5);
  }
}
