from spidev import SpiDev
import time
import os
import re

spi = SpiDev()
spi.open(0, 0)
spi.max_speed_hz = 4000
fastRate = 0.1 # delay between reads for text
slowRate = 0.5 # delay between reads for null characters
checkRate = slowRate
stringReceived = ""
vol = 10 # default volume level is 10. can be increased or decreased

while True:

    answer = spi.readbytes(1)


    if(answer == [0]):
        print("Received: nothing")
        checkRate = slowRate
        #when a complete string has been received
        if(stringReceived != ""):

            #check if the string is a command
            if("###" in stringReceived):
                if("volume" in stringReceived):
                    vol = int(re.search(r'\d+', stringReceived).group())

            #if the string is text to speak
            else:
                print("String Received: " + stringReceived)
                commandString = "espeak -a " + str(vol) + " \" " + stringReceived + "\""
                os.system(commandString)

            #reset the string
            stringReceived = ""
    else:
        print("Received: " + chr(answer[0]))
        checkRate = fastRate
        stringReceived += chr(answer[0])

    #sleep until time to check again
    time.sleep(checkRate)