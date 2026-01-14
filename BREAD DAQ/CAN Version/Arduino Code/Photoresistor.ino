/*
* Function for finding amount of light cast onto a photoresistor
* Modeled using a GL5528 photoresistor between 10 and 100 lux, gamma value may differ for other illumination values
*/
float resistorValue[] = {0,0,0,0,10000,10000}; //Current values of resistors used for the voltage divider

float photoresistorOutput(int channelNumber){
  //Protects from trying to read a digital pin
  /*
  if(!(channelPins[channelNumber] >= A0)){
    return 0;
  }*/

  //Get voltage using Arduino
  uint32_t voltageLevel = analogRead(channelPins[channelNumber]);
  float voltage = voltageLevel * VOLTAGE_PER_LEVEL;

  float gamma = 0.7; //Constant based on photoresistor
  float tenLuxResistance = 20000; //Photoresistor resistance at 10 lux

  //Calculate the resistance of the photoresistor and the illuminance correlated to that
  float photoResistance = (resistorValue[channelNumber]*voltage)/(5-voltage);
  float illuminance = (10*pow(tenLuxResistance,(1/gamma)))/pow(photoResistance,(1/gamma));

  return illuminance;
}