//MOLD 

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <BfButton.h>
#include <HX711_ADC.h>
#include <EEPROM.h>

//States of device
bool Calibrate = false;
bool boot = false;
bool homeMenu = false;
bool editGoal = false;
bool settings = false;

//Rotary Encoder Setup data pins
const int RotaryBtn = PD6;//Rotary Encoder Button pin
#define outputA 7 //pin dt
#define outputB 8 //pin clk
//Rotary Encoder Button Constructor
BfButton btn(BfButton::STANDALONE_DIGITAL, RotaryBtn, true, LOW);
//Rotary Encoder Variables
volatile bool A = false;
volatile bool B = false;
int aState;
int aLastState;

//Load Cell HX11 pins
const int HX711_dout = 4; //mcu > HX711 dout pin
const int HX711_sck = 5; //mcu > HX711 sck pin
//HX711 constructor
HX711_ADC LoadCell(HX711_dout, HX711_sck);
//Scale Variables
const int calVal_eepromAdress = 0;
unsigned long t = 0;
float  weight;//weight seen on scale
double goal = 1000;//weight goal
double goalTol = 0.2;//20% tol
double WeightVsGoal;
float known_mass = 1000;

//I2C LCD Constructor Connect to SCL and SDA pins 
LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display

//digital output of if weight is in tollerance 
const int inTolOut = 12;

//loadcell callabrate
bool notReady = true;

void setup() {
  // Screen Setup
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  //RotaryEncoder
  pinMode (outputA, INPUT);
  pinMode (outputB, INPUT);
  //buttons
  btn.onPress(pressHandler)
  .onDoublePress(pressHandler)
  .onPressFor(pressHandler, 1000);

  //Load Cell Start
  LoadCell.begin();
  //Set output pin for in tollarance 
  pinMode(inTolOut,OUTPUT);
  //Start Serial
  Serial.begin(57600);
  //start in boot
  boot = true;
}

void loop() {
  //Check for data LoadCell
  static boolean newDataReady = 0;
  if(LoadCell.update()){
    newDataReady = true;
  }
  //get value for new loadcelll load
  if(newDataReady){
    weight = LoadCell.getData();

    newDataReady = 0;
  }

  //Update the button
  btn.read();

  //Rotary Encoder Check for changes (rotation)
  aState = digitalRead(outputA);
    if(aState != aLastState ){
      if(digitalRead(outputB) != aState){ 
        
        //decrease by
        if(editGoal){
          goal = goal - 10;
        }
        
      }else{
        
        // increase by 
        if(editGoal){
          goal = goal +10;
        }
        
      }
    }
    aLastState = aState;

  //update screen
  const int serialPrintInterval = 500; //increase value to slow down serial print activity
  if (millis() > t + serialPrintInterval) {
      
    
  if(boot){
    lcd.setCursor(0,0); // set cursor to start of first line
    lcd.print("                ");//Clear LCD first line
    lcd.setCursor(0,1); // set cursor to start of first line
    lcd.print("                ");//Clear LCD Second line
    lcd.setCursor(0,0);
    lcd.println("BREAD MOLD      ");
    lcd.setCursor(0,1);
    lcd.println("Boot");
    calibrate();
    boot = false; 
    homeMenu = true;
  }
  if (homeMenu){
    lcd.setCursor(0,0); // set cursor to start of first line
    lcd.print("                ");//Clear LCD first line
    lcd.setCursor(0,1); // set cursor to start of first line
    lcd.print("                ");//Clear LCD Second line
    lcd.setCursor(0,0); // set cursor to start of first line
    lcd.print("Weight:");
    lcd.setCursor(8,0);
    lcd.print((double)weight);
    lcd.setCursor(0,1); // set cursor to start of first line
    lcd.print("W/G:");
    lcd.setCursor(5,1);
    WeightVsGoal = ((double)weight / goal)*100;
    lcd.print(WeightVsGoal);
    lcd.setCursor(15,1);
    lcd.print("%");
    //Check to tolarance
    if(WeightVsGoal>(100+(goalTol*100))){
      digitalWrite(inTolOut, HIGH);
    }else if(WeightVsGoal<(100-(goalTol*100))){
      digitalWrite(inTolOut, HIGH);
    }
    else{
      digitalWrite(inTolOut, LOW);
    }
  }
  if (editGoal){
    lcd.setCursor(0,0); // set cursor to start of first line
    lcd.print("                ");//Clear LCD first line
    lcd.setCursor(0,1); // set cursor to start of first line
    lcd.print("                ");//Clear LCD Second line
    lcd.setCursor(0,0); // set cursor to start of first line
    lcd.print("Set Goal");
    lcd.setCursor(0,1); // set cursor to start of first line
    lcd.print("Goal:");
    lcd.setCursor(6,1);
    lcd.print((double)goal);
  }
  if (settings){
    lcd.setCursor(0,0); // set cursor to start of first line
    lcd.print("                ");//Clear LCD first line
    lcd.setCursor(0,1); // set cursor to start of first line
    lcd.print("                ");//Clear LCD Second line
    lcd.setCursor(0,0); // set cursor to start of first line
    lcd.print("Single Back");
    lcd.setCursor(0,1); // set cursor to start of first line
    lcd.print("Hold Calibrate");
  }
  
    t = millis();
  }


}

//button cottrol state
void pressHandler (BfButton *btn, BfButton::press_pattern_t pattern){
  switch (pattern) {
    
    case BfButton::SINGLE_PRESS:
      Serial.println("Single Press");
      if(Calibrate){
        notReady = false;
      }
      else if(homeMenu){
        homeMenu = false;
        editGoal = true;
      }
      else if(editGoal){
        editGoal = false;
        homeMenu = true;
      }
      else if(settings){
        settings = false;
        homeMenu = true;
      }

    break;

    
    case BfButton::DOUBLE_PRESS:
      

    break;

    
    case BfButton::LONG_PRESS:
    Serial.println("Hold Press");
      if(homeMenu){
        homeMenu = false;
        settings = true;
      }
      else if(settings){
        notReady = true;
        calibrate();
        settings = false;
        homeMenu = true;
      }
    
    
    break;
  }
}

void calibrate(){
  Calibrate = true;
  Serial.println("Calibrate");
  delay(2000);//wait 2 sec for loadcell board to stablilize
  lcd.setCursor(0,0); // set cursor to start of first line
  lcd.print("                ");//Clear LCD first line
  lcd.setCursor(0,1); // set cursor to start of first line
  lcd.print("                ");//Clear LCD Second line
  lcd.setCursor(0,0);
  lcd.println("Clear Plate     ");
  lcd.setCursor(0,1);
  lcd.println("For Tare        ");
  delay(2000);
  //wait for button press
  while(notReady){
    btn.read();
  }
  notReady = true;
  LoadCell.tare();
  lcd.setCursor(0,0); // set cursor to start of first line
  lcd.print("                ");//Clear LCD first line
  lcd.setCursor(0,1); // set cursor to start of first line
  lcd.print("                ");//Clear LCD Second line
  lcd.setCursor(0,0);
  lcd.println("Place Know      ");
  lcd.setCursor(0,1);
  lcd.println("Mass: ");
  while(notReady){
    btn.read();
    //use rotary encoder to change known mass 
    aState = digitalRead(outputA);
    if(aState != aLastState ){
      if(digitalRead(outputB) != aState){ 
        //decrease by
        known_mass = known_mass - 10;
      }else{
        // increase by 
        known_mass = known_mass + 10;
      }
    }
    aLastState = aState;
    const int serialPrintInterval = 500; //increase value to slow down serial print activity
    if (millis() > t + serialPrintInterval) {
    lcd.setCursor(6,1);
    lcd.println("          ");//clear old known mass
    lcd.setCursor(6,1);
    lcd.println(known_mass);
     t = millis();
    }
  }
  notReady = true;

  LoadCell.refreshDataSet(); //refresh the dataset to be sure that the known mass is measured correct
  float newCalibrationValue = LoadCell.getNewCalibration(known_mass); //get the new calibration value

  #if defined(ESP8266)|| defined(ESP32)
        EEPROM.begin(512);
  #endif
        EEPROM.put(calVal_eepromAdress, newCalibrationValue);
  #if defined(ESP8266)|| defined(ESP32)
        EEPROM.commit();
  #endif
        EEPROM.get(calVal_eepromAdress, newCalibrationValue);
  lcd.setCursor(0,0); // set cursor to start of first line
  lcd.print("                ");//Clear LCD first line
  lcd.setCursor(0,1); // set cursor to start of first line
  lcd.print("                ");//Clear LCD Second line
  Calibrate = false;
  lcd.setCursor(0,0); // set cursor to start of first line
  lcd.print("Calibration");//LCD first line
  lcd.setCursor(0,1); // set cursor to start of first line
  lcd.print("Complete");//LCD Second line

}



