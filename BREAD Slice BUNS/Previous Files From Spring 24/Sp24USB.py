import serial
import time
import MySQLdb as mdb

arduino = serial.Serial("/dev/ttyUSB0")  #check what USB port your arduino is connected to
arduino.baudrate=9600

con = mdb.connect('localhost', 'testing', 'testing','testdb') #replace with your characteristics ('localhost', 'username', 'password', 'databaseName')

try:
    while(1):
        time.sleep(1)
        storedData = ""
        newData = ""
        reading = True
        
        while reading:
            newData = arduino.readline().decode()
            if '\n' in newData:
                storedData += newData
                reading = False
            else:
                storedData += newData

        storedData = storedData.strip()
        pieces = storedData.split("\t")
        
        if len(pieces) >= 2:
            name = "Barcode"
            code = pieces[1]
            
            print(name)
            print(code)

            try:
                cursor = con.cursor()
                cursor.execute("""INSERT INTO count VALUES(%s, %s)""", (name, code)) #replace 'count' with your table name
                con.commit()
                cursor.close()
            except mdb.Error as e:
                print("Error inserting data", e)
                con.rollback()
finally:
    if con:
        con.close()
