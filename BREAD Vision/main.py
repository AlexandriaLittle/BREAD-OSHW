import cv2
from numpy import *
import time
from picamera2 import Picamera2

import sys
import smbus2 as smbus

# Slave Addresses
I2C_SLAVE_ADDRESS = 11

from Colorintegration import ColorIntegration
from detect_and_track import DetectAndTrack

#image frame
height = 720
width = 1280
camera = Picamera2()
# camera.start_preview(Preview.QTGL)
# preview_config = picam2.create_preview_configuration()
capture_config = camera.create_still_configuration(main={"size": (width, height)})


# picam2.configure(preview_config)
camera.configure(capture_config)
camera.start()
# camera.resolution = (width, height)

time.sleep(2)
# #for loop to index color until told to stop.
# while(True):
    # # camera.capture("img.jpg")
    # # image = cv2.imread("img.jpg")
    # # image = picam2.switch_mode_and_capture_image(capture_config)
    # camera.capture_file("img.jpg")
    # image = cv2.imread("img.jpg")
    
    # print("Color Intregration:")
    # print(ColorIntegration.process_image(image))

    # print("Detect And Track:")
    # print(DetectAndTrack.process_image(image))

    # time.sleep(2)
    
    # break



# This function converts a string to an array of bytes.
def ConvertStringsToBytes(src):
  converted = []
  for b in src:
    converted.append(ord(b))
  return converted


def main(args):
    I2Cbus = smbus.SMBus(1)
    
    BytesToSend = 0;
    #for loop to index color until told to stop.
    while(True):
        # # cmd = input("Enter command: ")
        
        # # BytesToSend = ConvertStringsToBytes(cmd)
        # BytesToSend += 1;
        # print("\nSent BREAD Loaf the " + str(BytesToSend) + " command.")
        # # print(BytesToSend)
        # # I2Cbus.write_i2c_block_data(I2C_SLAVE_ADDRESS, 0x00, BytesToSend)
        # I2Cbus.write_byte_data(I2C_SLAVE_ADDRESS, 0x00, BytesToSend)
        # time.sleep(0.5)
        
        # try:
            # # data = I2Cbus.read_i2c_block_data(I2C_SLAVE_ADDRESS,0x00,2)
            # data = I2Cbus.read_byte_data(I2C_SLAVE_ADDRESS, 0)
            # print("recieve from BREAD Loaf:", data)
            
        # except:
            # print("remote i/o error")
            # time.sleep(0.5)
        
        
        camera.capture_file("img.jpg")
        image = cv2.imread("img.jpg")
        
        print("Color Intregration:")
        print(ColorIntegration.process_image(image))

        print("Detect And Track:")
        print(DetectAndTrack.process_image(image))

        time.sleep(1)
            
    return 0


if __name__ == '__main__':
     try:
        main(sys.argv)
     except KeyboardInterrupt:
        print("program was stopped manually")
     input()
