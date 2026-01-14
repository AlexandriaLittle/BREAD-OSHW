// Modified header file from Arduino library by Anne Mahaffey
// Needed to be able to set AD7193_CS_PIN, so it was changed from a define to a variable that is set by the AD7193_begin() function
// Was originally class based but I am not experienced enough with Arduino or C++ to make it work properly
//
// Original code available at https://www.arduino.cc/reference/en/libraries/ad7193/

#ifndef MYAD7193_h
#define MYAD7193_h

#include <Arduino.h>
#include <SPI.h>

//#define AD7193_CS_PIN     9  // define the chipselect
#define AD7193_RDY_STATE  MISO   // pin to watch for data ready state

/* AD7193 Register Map */
#define AD7193_REG_COMM         0 // Communications Register (WO, 8-bit) 
#define AD7193_REG_STAT         0 // Status Register         (RO, 8-bit) 
#define AD7193_REG_MODE         1 // Mode Register           (RW, 24-bit 
#define AD7193_REG_CONF         2 // Configuration Register  (RW, 24-bit)
#define AD7193_REG_DATA         3 // Data Register           (RO, 24/32-bit) 
#define AD7193_REG_ID           4 // ID Register             (RO, 8-bit) 
#define AD7193_REG_GPOCON       5 // GPOCON Register         (RW, 8-bit) 
#define AD7193_REG_OFFSET       6 // Offset Register         (RW, 24-bit 
#define AD7193_REG_FULLSCALE    7 // Full-Scale Register     (RW, 24-bit)

/* Communications Register Bit Designations (AD7193_REG_COMM) */
#define AD7193_COMM_WEN         (1 << 7)           // Write Enable. 
#define AD7193_COMM_WRITE       (0 << 6)           // Write Operation.
#define AD7193_COMM_READ        (1 << 6)           // Read Operation. 
#define AD7193_COMM_ADDR(x)     (((x) & 0x7) << 3) // Register Address. 
#define AD7193_COMM_CREAD       (1 << 2)           // Continuous Read of Data Register.



//AD7193(void); //need to add this function
//bool begin(Stream &serialPort = Serial);  // does this help me specify serial?
	
bool AD7193_begin(int CS_Pin);
void AD7193_Reset(void);
void AD7193_Calibrate(void);

void AD7193_SetPGAGain(int gain);
void AD7193_SetAveraging(int filterRate);
void AD7193_SetChannel(int channel);
	
void AD7193_SetPsuedoDifferentialInputs(void);
void AD7193_AppendStatusValuetoData(void);
	
unsigned long AD7193_ReadADCChannel(int channel);
unsigned long AD7193_ReadADCData(void);
void AD7193_IntitiateSingleConversion(void);
void AD7193_WaitForADC(void);


float AD7193_DataToVoltage(long rawData);
float AD7193_TempSensorDataToDegC(unsigned long rawData);
	
	
unsigned long AD7193_GetRegisterValue(unsigned char registerAddress,
                                      unsigned char bytesNumber,
                                      unsigned char modifyCS);
void AD7193_SetRegisterValue(unsigned char registerAddress,
                            unsigned long registerValue,
                            unsigned char bytesNumber,
                            unsigned char modifyCS);

	
void AD7193_ReadRegisterMap(void);

int AD7193_CS_PIN;

//void SetChannelSelect(unsigned long wordValue);
//void ChannelEnable(int channel);
	
//void SingleConversionAndReadADC(long unsigned int *ADCDataByChannel);  // this needs to be a pointer
//void DisplayADCData(long unsigned int ADCDataByChannel[]);
//void WriteAllRegisters(void);
#endif

/*blah blah*/