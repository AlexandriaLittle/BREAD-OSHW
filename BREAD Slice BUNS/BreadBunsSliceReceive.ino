#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 17    // Choose any available GPIO for CE
#define CSN_PIN 5   // Choose any available GPIO for CSN

// RF24 radio
RF24 radio(CE_PIN, CSN_PIN); // CE, CSN
const byte address[6] = "00001";

//Display
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Struct for combining data
struct transmitData {
  uint8_t j;              // Number of valid characters in Scanned
  char Scanned[31];       // Character array to hold the scanned data
};

// Initialize the transmitData struct
void transmit_Init(struct transmitData* Transmitted) {
  memset(Transmitted->Scanned, 0, sizeof(Transmitted->Scanned)); // Clear the array
  Transmitted->j = 0;
}

struct transmitData dat;

unsigned long totalMessages = 0;      // Total count of messages received
unsigned long startTime;              // Time when program started
unsigned long lastReportTime = 0;     // Last time the rate was reported
unsigned long reportInterval = 5000;  // Report interval in milliseconds (5 seconds)

void setup() {
  Serial.begin(9600);
  Serial.println("Receiver Starting");

  // Initialize I2C with custom pins if needed
  //Wire.begin(5, 17);  //SDA, SCL

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  display.clearDisplay();
  display.setCursor(0, 0); //oled display
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("");
  display.display();

  // Begin radio with specified CE and CSN
  if (!radio.begin()) {
    Serial.println("Radio hardware not responding!");
    while (1); // Stop if the radio is not responding
  }
  
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  
  transmit_Init(&dat);
  startTime = millis(); // Capture the initial start time
}

void loop() {
  if (radio.available()) { // Check if there is incoming data
    display.clearDisplay();
    display.display();
    display.setCursor(0, 0); //oled display
    transmit_Init(&dat);   // Reset the struct for new data

    // Read the data from the radio
    radio.read(&dat, sizeof(dat));

    // Print each character up to the count specified in j
    Serial.print("Barcode: ");
    Serial.print("\t");
    for (int i = 0; i < dat.j && i < 31; i++) {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.print(dat.Scanned[i]);
      display.display();
      Serial.print(dat.Scanned[i]);
    }
    
    Serial.println("\t");
    Serial.println();
    display.clearDisplay();
    
    // Increment the total message count
    totalMessages++;
  }
  
  // Calculate and print the average rate every 5 seconds
  unsigned long currentTime = millis();
  if (currentTime - lastReportTime >= reportInterval) {
    // Calculate the total elapsed time in minutes since the start of the program
    float elapsedMinutes = (currentTime - startTime) / 60000.0;

    // Calculate the all-time average rate (messages per minute) This gets sent to the Loaf
    float averageRate = totalMessages / elapsedMinutes;

    // Print the average rate
    //Serial.print("Average rate: ");
    //Serial.print(averageRate);
    //Serial.println(" scans/minute");

    // Update the last report time
    lastReportTime = currentTime;
  }
}
