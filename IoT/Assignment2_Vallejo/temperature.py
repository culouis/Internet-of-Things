#Omar Vallejo
#My SQL Lab 2
#1/9/2018

import random
#import mysql.connector
import time
import datetime

cnx = mysql.connector.connect(user='root',datatbase = 'Vallejo_IoTDatabase')
cursor = cnx.cursor()

ts = time.time()
dayntime =datetime.datetime.fromtimestamp(ts).strftime('%y-%m-%d %H:%M:%S')
fahr = random.randint(0,100)
celcius = (fahr - 32) *1.8
row_id= 1
device_id= 33
device_id=str(device_id)
row_id=str(row_id)
fahr=str(fahr)
celcius=str(celcius)

add_temperature = ("INSERT INTO Vallejo_IoTDatabase VALUES (",
                   row_id, ", ",device_id, ", ",fahr,", ", celcius,", ",dayntime,")")
cursor.execute(add_temperature)
#row_id= row_id+1

cnx.commit()
cursor.close()
cnx.close()

    
