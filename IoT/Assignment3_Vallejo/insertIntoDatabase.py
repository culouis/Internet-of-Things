#####################
# Omar VALLEJO      #
# 1/12/2018         #
# Assignment 3      #
#####################


import socket
import sys
import mysql.connector
from datetime import datetime

#Create the socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#bind the socket to the port
server_address = ('192.168.0.10', 40003)
print >> sys.stderr, 'starting up on %s port %d' % server_address
sock.bind(server_address)

print >>sys.stderr, '\nwaiting to recieve message'
data, address = sock.recvfrom(16) #recieves data

while True:
    #Creates connection to database
    cnx = mysql.connector.connect(user='root', database='VALLEJO_IOTDATABASE', password='mynewpassword')
    #Creates the cursor
    cursor = cnx.cursor()

    #Creates the VALUES
    output= data.split(",")
    photoData = output[1]
    soundData = output[0]
    deviceID = 'device1'
    insertDate = datetime.now().strftime("%y-%m-%d-%H:%M")

    #format the string
    insertIntoDB = 'INSERT INTO DATA_TABLE3 (DEVICE_ID, \
    SOUND_DATA,\
    PHOTORESISTOR_DATA,\
     DATE_)  VALUES (\'%s\',\'%s\', \'%s\', \'%s\')'%(deviceID,soundData,photoData,insertDate)

    #executes the insert statement in the database
    cursor.execute(insertIntoDB)

    #commits the data to the database
    cnx.commit()

#after loop, close cursor, then close connection
cursor.close()
cnx.close()
