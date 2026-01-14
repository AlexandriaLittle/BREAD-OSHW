// Thermocouple conversions taken from example code by Anne Mahaffey in Arduino library, AD7193.h

/*
* Function for finding temperature at thermocouple
* Modeled using a Digilent 240-080 K-type thermocouple
*/
float thermocoupleKOutput(uint32_t channelNumber){
  unsigned long chData;
  unsigned long chipTempData;

  //Read channel data
  chData = (AD7193_ReadADCChannel(channelPins[channelNumber])) >> 8;     // last 8 bits of ch0Data are status bits, and not data bits
  //Serial.print("  CH0 data: ");
  //Serial.print(chData, HEX);
  
  // Read on-chip temperature data
  chipTempData = (AD7193_ReadADCChannel(8) >> 8);   // last 8 bits of ch0Data are status bits, and not data bits
  //Serial.print("  CH8 data (temperature): ");
  //Serial.println(chipTempData, HEX);         
  
  // Convert AD7193 temperature data to temperature (degC), 
  // and calculate equivalent voltage - used for cold junction compensation
  float ambientTemp = AD7193_TempSensorDataToDegC(chipTempData);
  float referenceVoltage = Thermocouple_Ktype_TempToVoltageDegC(ambientTemp);

  // measure thermocouple voltage
  float thermocoupleVoltage = AD7193_DataToVoltage(chData);

  // Cold Junction Compensation
  float compensatedVoltage = thermocoupleVoltage + referenceVoltage;
  float compensatedTemperature = Thermocouple_Ktype_VoltageToTempDegC(compensatedVoltage);

  if(FAHRENHEIT == output[channelNumber]){
    compensatedTemperature = (compensatedTemperature*9./5.) + 32;
  }

  //Serial.print(compensatedTemperature,HEX);

  return compensatedTemperature;
}

float Thermocouple_Ktype_VoltageToTempDegC(float voltage) {
  // http://srdata.nist.gov/its90/type_k/kcoefficients_inverse.html
  float coef_1[] = {0, 2.5173462e1, -1.1662878, -1.0833638, -8.9773540e-1};            // coefficients (in mV) for -200 to 0C, -5.891mv to 0mv
  float coef_2[] = {0, 2.508355e1, 7.860106e-2, -2.503131e-1, 8.315270e-2};            // coefficients (in mV) for 0 to 500C, 0mv to 20.644mv
  float coef_3[] = {-1.318058e2, 4.830222e1, -1.646031, 5.464731e-2, -9.650715e-4};    //whoa, that's hot...
  int i = 5;  // number of coefficients in array
  float temperature;

  float mVoltage = voltage * 1e3;

  if(voltage < 0) {
    temperature = power_series(i, mVoltage, coef_1);
  }else if (voltage > 20.644){
    temperature = power_series(i, mVoltage, coef_3);
  }else{
    temperature = power_series(i, mVoltage, coef_2);
  }

  return(temperature);
}


float Thermocouple_Ktype_TempToVoltageDegC(float temperature) {
  // https://srdata.nist.gov/its90/type_k/kcoefficients.html
  float coef_1[] = {0, 0.3945013e-1, 0.2362237e-4, -0.3285891e-6, -0.4990483e-8};            // coefficients (in mV) for -270 to 0C, -5.891mv to 0mv
  float coef_2[] = {-0.17600414e-1, 0.38921205e-1, 0.1855877e-4, -0.9945759e-7, 0.31840946e-9};            // coefficients (in mV) for 0 to 1372C, 0mv to ....
  float a_coef[] = {0.1185976, -0.1183432e-3, 0.1269686e3};
  int i = 5;  // number of coefficients in array

  float mVoltage;
  float a_power = a_coef[1] * pow((temperature - a_coef[2]), 2);
  float a_results = a_coef[0] * exp(a_power);

  if(temperature < 0) {
    mVoltage = power_series(i, temperature, coef_2) + a_results;
  } else {
    mVoltage = power_series(i, temperature, coef_1);
  }

  return(mVoltage / 1e3);
}

float power_series(int n, float input, float coef[]){
  delay(10);      
  int i;
  float sum=coef[0];
  for(i=1;i<=(n-1);i++){
    sum=sum+(pow(input, (float)i)*coef[i]);
  }
  return(sum);
}
