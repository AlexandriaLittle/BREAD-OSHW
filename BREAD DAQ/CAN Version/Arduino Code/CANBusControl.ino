//For interrupts?
unsigned char flagRecv = 0;
byte len = 0;

uint8_t initializeCAN(){
  if(CAN.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
    lcd.setCursor(0,0);
    lcd.print(F("MCP2515 Initialized Successfully!"));
    delay(750);
    CANconn = 1;
  }
  else {
    lcd.setCursor(0,0);
    lcd.print(F("Error Initializing MCP2515..."));
    delay(750);
    CANconn = 0;
    return;
  }
  
  CAN.setMode(MCP_NORMAL);

  /*
      set filter, we can receive id from 0x00 ~ 0x05
      To include more than 6 ids in the whitelist, custom filtering will need to be written that acts on each message. Set masks and filters to 0x00

      Mask and filters include ID in first 12 bits, then first 16 bits of data (or for extended, uses full 28 bits)
  */
  //High Priority Mask/Filters
  CAN.init_Mask(0,0,0x7c00000);                // Init first mask...
  CAN.init_Filt(0,0,BREAD_DAQ << 16);          // Init first filter...
  CAN.init_Filt(1,0,BREAD_VISION << 16);       // Init second filter...
  
  //Low Priority Mask/Filters
  CAN.init_Mask(1,0,0x7c00000);                // Init second mask... 
  CAN.init_Filt(2,0,BREAD_BUNS << 16);         // Init third filter...
  CAN.init_Filt(3,0,0x1040000);                // Init fourth filter...
  CAN.init_Filt(4,0,0x1060000);                // Init fifth filter...
  CAN.init_Filt(5,0,0x1070000);                // Init sixth filter...

  //Announce presence to system, in case of duplicate DAQs. Any duplicates with the 0x0 dupID will respond with a command to increment this DAQs dupID
  CAN.sendMsgBuf(localID | ESTABLISH_ID, 0, 1, 0x0); 
  return CAN_OK;
}

void checkCAN(){
  //if(CANconn == 1){
    unsigned char len = 0;
    unsigned char buf[8];
    unsigned long canID;

    if (CAN_MSGAVAIL == CAN.checkReceive()) {         // check if data coming
          
      CAN.readMsgBuf(&canID, &len, buf);    // read data,  canID: ID of message, len: data length, buf: data buf

      //If this device is being written to (localID was sent with the 0 command)
      if(canID == (localID | WRITE_DEVICE)){
        //Sending an empty message indicates that an ID with the same dupID is already on the system
        if(len == 0){
          changeID();
        }
        //Otherwise change settings on device as needed
      }

      //If another DAQ is sending data
      else if(canID == (BREAD_DAQ | SEND_DATA)){
        //Write to SD card with dupID?
        SDwriteCANDAQ(buf);
      }

      //If another DAQ is trying to Establish the same ID
      else if(canID == (localID | ESTABLISH_ID)){
        //Send message indicating that this ID is taken
        CAN.sendMsgBuf(localID | WRITE_DEVICE, 0, 0, 0x0); 
      }

      //ID Matches Vision
      else if ((canID & 0x7C0) == BREAD_VISION){
        //Do Something

        //For receiving data from Vision
        if((canID & 0x007) == SEND_DATA){
          //Log data
          SDwriteVision(len,buf);
        }
      }
    }
  //}
}

//Sends data on CAN line for any slices that want it to read
void sendCANData(void* data,uint32_t channel){
  //if(CANconn == 1){
    //Sends data type in first byte, then channel number in second byte, then units in the third byte, then float data value in final 4 bytes
    //Any recipients will need at least part of BREAD_DAQ.h
    unsigned char buf[7];
    buf[0] = (char) sensorType[channel];
    buf[1] = (char) channel;
    buf[2] = (char) output[channel];
    buf[3] = ((char*) data)[0];
    buf[4] = ((char*) data)[1];
    buf[5] = ((char*) data)[2];
    buf[6] = ((char*) data)[3];
    *(buf+3) = data;

    //Assembles ID, does not use extended id, 
    CAN.sendMsgBuf(localID | SEND_DATA, 0, 7, buf); 
  //}
}

void changeID(){
  //if(CANconn == 1){
    dupID++;
    localID = BREAD_DAQ | (dupID << 3);
    //Announce presence to system, in case of duplicate DAQs. Any duplicates with the 0x0 dupID will respond with a command to increment this DAQs dupID
    CAN.sendMsgBuf(localID | ESTABLISH_ID, 0, 0, 0x0); 
  //}
}

void MCP2515_ISR() {
    flagRecv = 1;
}

