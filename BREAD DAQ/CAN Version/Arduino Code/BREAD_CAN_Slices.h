#ifndef BREAD_CAN_SLICES_Hc:\Users\jklap\Downloads\main.cpp
#define BREAD_CAN_SLICES_H

//Stores codes for slices that have implemented the CAN protocol
//First 5 bits identify slice type i.e. DAQ or Vision
//Next 3 reserved for Slice duplication tags (First connected DAQ takes 0b000, Second connected DAQ will have 0b001, etc)
//Final 3 bits reserved for message type

//Slice types
const unsigned int BREAD_LOAF = 0x0;
const unsigned int BREAD_DAQ = 0x01 << 6;
const unsigned int BREAD_VISION = 0x02 << 6;
const unsigned int BREAD_BUNS = 0x03 << 6;


//Message Types
const unsigned int WRITE_DEVICE = 0x0;
const unsigned int SEND_DATA = 0x1;
const unsigned int ESTABLISH_ID = 0x7;


//Vision Analysis Types
const unsigned int COLOR_INTEGRATION = 0x0;
const unsigned int OBJECT_DETECTION = 0x1;
const unsigned int SPECTROMETER = 0x2;
#endif