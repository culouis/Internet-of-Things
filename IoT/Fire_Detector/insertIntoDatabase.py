#####################
# Omar VALLEJO      #
# 1/19/2018         #
# final Assignment     #
#####################


import socket
import sys
import mysql.connector
from datetime import datetime

#Create the socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#bind the socket to the port
server_address = ('192.168.0.10', 10397)
print >> sys.stderr, 'starting up on %s port %d' % server_address
sock.bind(server_address)

print >>sys.stderr, '\nwaiting to recieve message'
data, address = sock.recvfrom(16) #recieves data

while True:
    #Creates connection to database
    cnx = mysql.connector.connect(user='root', database='GROUP_THREE', password='mynewpassword')
    #Creates the cursor
    cursor = cnx.cursor()

    #Creates the VALUES
    output= data.split(",")
    fire = output[1]
    timer = output[0]
    deviceID = 'device10003'
    #insertDate = datetime.now().strftime("%y-%m-%d-%H:%M")

    #format the string
    insertIntoDB = 'INSERT INTO Flame_Table (DEVICE_ID, \
    Fire_Detection,\
    Time_Lit)  VALUES (\'%s\',\'%s\', \'%s\')'%(deviceID,fire,timer)

    #executes the insert statement in the database
    cursor.execute(insertIntoDB)

    #commits the data to the database
    cnx.commit()

    #after loop, close cursor, then close connection
    cursor.close()
    cnx.close()
