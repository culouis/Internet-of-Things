import socket
import sys

#Create the socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

#bind the socket to the port
server_address = ('192.168.0.10', 40000)
print >> sys.stderr, 'starting up on %s port %d' % server_address
sock.bind(server_address)

while True:
    print >>sys.stderr, '\nwaiting to recieve message'
    data, address = sock.recvfrom(16)

    print >>sys.stderr, "\nreceived %s bytes from %s" % (len(data), address)
    print >>sys.stderr, data
