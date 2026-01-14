import mysql.connector
from mysql.connector import Error
import os
import datetime
import time

DatabaseIP = "192.168.50.74"
db_name = 'sys'
table_name = 'daq logs'
username = 'python'
password = 'python'

tempLog = []

def readFile(filepath):
    with open(filepath, "r") as file:
        for line in file:
            words = line.split()
            # Print each word individually
            tempLog.append(words)
            

def create_server_connection(host_name, user_name, user_password):
    connection = None
    try:
        connection = mysql.connector.connect(
            host=host_name,
            user=user_name,
            passwd=user_password
        )
        print("MySQL Database connection successful")
    except Error as err:
        print(f"Error: '{err}'")

    return connection

def create_database(connection, query):
    cursor = connection.cursor()
    try:
        cursor.execute(query)
        print("Database created successfully")
    except Error as err:
        print(f"Error: '{err}'")

def create_db_connection(host_name, user_name, user_password, db_name):
    connection = None
    try:
        connection = mysql.connector.connect(
            host=host_name,
            user=user_name,
            passwd=user_password,
            database=db_name
        )
        print("MySQL Database connection successful")
    except Error as err:
        print(f"Error: '{err}'")

    return connection

def execute_query(connection, query):
    cursor = connection.cursor()
    try:
        cursor.execute(query)
        connection.commit()
        print("Query successful")
    except Error as err:
        print(f"Error: '{err}'")

# Get current directory
directory = os.getcwd()

# Get the list of files in the directory
files = os.listdir(directory)
directory = directory + '\\'

# print(directory)
# print(files)

for i in range(len(files)):
    if files[i].find('LOG_') == 0:
        readFile(files[i])

print(len(tempLog),' Logs found')

try:
    conn = create_db_connection(DatabaseIP,username,password,db_name)
    cursor = conn.cursor()
except:
    print("error on connect!")

try:
    query = "INSERT INTO `"+db_name+"`.`"+table_name+"` (`Timestamp`, `Value`, `Unit`, `Channel`) VALUES (%s, %s, %s, %s)"

    for j in range(len(tempLog)):
        timestamp = tempLog[j][0].replace('/', '-') + ' ' + tempLog[j][1]
        Value = tempLog[j][3]
        max_value_length = 4  # Adjust according to your column size
        if len(Value) > max_value_length:
            Value = Value[:max_value_length]
        Unit = tempLog[j][4]
        Channel = tempLog[j][2]
        data = (timestamp, Value, Unit, Channel)
        cursor.execute(query, data)
        # print("running...")

    cursor.close()
    conn.commit()
    conn.close()
    print("Translaiton Complete :)")
except:
    print("error on insert!")
time.sleep(2.5)