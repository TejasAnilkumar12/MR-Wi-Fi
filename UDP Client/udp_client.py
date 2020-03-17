#import socket library 
import socket 


# address = (server ip address, server port number)
address= ( '192.168.10.243', 5000)
# create a UDP SOCKET -> SOCK_DGRAM
# for TCP SOCKET -> SOCK_STREAM (not valid for current example)
client_socket =socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
#Timeout of 1 second 
client_socket.settimeout(1) 
 
while(1):
    # data to be sent to UDP server
    dataToServer = "A"

    #sendto( data, (address,port))
    client_socket.sendto( dataToServer.encode(), address) 
 
    try:
        #read from buffer size of 2048 bytes
        datafromServer, ip = client_socket.recvfrom(2048)
        print("{}: {}".format(ip, datafromServer.decode()))
 
    except:
        pass
 
    
 
    
