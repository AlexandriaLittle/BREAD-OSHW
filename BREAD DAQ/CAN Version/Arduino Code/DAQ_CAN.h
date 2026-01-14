#ifndef DAQ_CAN
#define DAQ_CAN

//Setup for CAN communication
#define CAN_SPI_CS A0
#define CAN_INT 3

//Storage for ID
unsigned int localID = BREAD_DAQ;
unsigned int dupID = 0;

uint8_t initializeCAN();
void checkCAN();
void sendCANData(void* data,uint32_t channel);
void changeID();

#endif