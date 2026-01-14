ISR (PCINT1_vect){

  //Delay waits for switches to finish bouncing before checking interrupts - prevents double inputs
  delay(100);

  //Check pin 1 (button 1)
  if(PINC & B0100){
    //debounce(1);
    if(HIGH == digitalRead(SW2pin)){
      curChannel++;
      if(curChannel >= NUM_CHANNELS){curChannel = 0;}

      changeLabel();

      
    }
  }

  if(PINC & B0010){
    //debounce(2);
    if(HIGH == digitalRead(SW1pin)){
      //Change to different sensor type
      //sensorType[curChannel]--;
      //if(NULL_S == sensorType[curChannel]){sensorType[curChannel] = THERMOCOUPLE_K;}
      //changeLabel();

      //Change to next output type
      output[curChannel]--;
      if(NULL_T == output[curChannel]) {output[curChannel] = CELSIUS;}
      if(NULL_C == output[curChannel]) {output[curChannel] = AMPS;}
      if(NULL_P == output[curChannel]) {output[curChannel] = LUX;}
    }
  }
}
