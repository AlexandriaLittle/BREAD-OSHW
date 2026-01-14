import smbus2 as smbus
import sys
import time
from multiprocessing import shared_memory

bus = smbus.SMBus(1)
# Temporary, will automate address collection for I2C at some point, if reading this and not implemented
# you need to run the terminal command i2cdetecy -y 0 to find the address of the connected arduino
addr = 8


def stringtobyte(src):
    conv = []
    for b in src:
        conv.append(ord(b))
    return conv


while True:
    try:
        command = bus.read_byte(8)
        # The offset in the second command determines which register we are reading, audiono uses reg 12
        # Command 1 will correlate to detect and track being run
        if command == 1:
            sendbyte = stringtobyte("Detect and Track")
            bus.write_i2c_block_data(addr, 0, sendbyte)
            # Python 3 way to run a python script
            exec(open("detectandtrack.py").read())
            exit()
        if command == 2:
            # Command 2 will correlate to xml download
            sendbyte = stringtobyte("Casscade builder")
            bus.write_i2c_block_data(addr, 0, sendbyte)
            exec(open("xmlconstruct.py").read())
            exit()
        if command == 3:
            # Command 3 will run exclusive Vision sensor
            sendbyte = stringtobyte("Vision")
            bus.write_i2c_block_data(addr, 0, sendbyte)
            exec(open("vision.py").read())
            exit()
        if command == 4:
            # Command 4 will run QC check
            sendbyte = stringtobyte("QC Check")
            bus.write_i2c_block_data(addr, 0, sendbyte)
            exec(open("qctalk.py").read())
            time.sleep(0.5)
            exec(open("qcdetect.py").read())
            exec(open("qccolor.py").read())
            exit()
    except:
        print("no response from loaf")
        time.sleep(0.5)
