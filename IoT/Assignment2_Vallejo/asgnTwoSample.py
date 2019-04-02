import random
from datetime import datetime
import mysql.connector

#Creates connection to database
cnx = mysql.connector.connect(user='root', database='IoTDatabase', password='mynewpassword')
#Creates the cursor
cursor = cnx.cursor()

#start our loop for the 20 readings
for i in range(20):
    #create data variables
    fahrenheit = random.randint(1, 100)
    insertDate = datetime.now().strftime("%y-%m-%d-%H:%M")
    celsius = (fahrenheit-32)*5/9
    deviceID = 'device1'

    #creates insert statement
    data = 'INSERT INTO TEMPERATURE_READINGS (DEVICE_ID, TEMPERATURE_FAR, TEMPERATURE_CEL, INSERT_DATE) VALUES (\'%s\', %0.4f, %0.4f, \'%s\')'%(deviceID, fahrenheit, celsius, insertDate)

    #prints the statements for debug purposes
    print (data)

    #executes the insert statement in the database
    cursor.execute(data)

    #commits the data to the database
    cnx.commit()
    #delays for 10 seconds
    time.sleep(10)

#after loop, close cursor, then close connection
cursor.close()
cnx.close()
