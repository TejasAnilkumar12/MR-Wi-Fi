#include <Ethernet.h> //Load Ethernet Library
#include <EthernetUdp.h> //Load the Udp Library
#include <SPI.h> //Load SPI Library
 
 
String data = "Wi-Fi tEAM rOCKs";

byte mac[] ={ 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE}; 
IPAddress ip(192, 168, 10, 243); 
unsigned int localPort = 5000; 
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
String request;
int packetSize; 
EthernetUDP Udp; 

void setup() {
  
  Serial.begin(9600); 
  //Start Ethernet at 192.168.10.243 
  Ethernet.begin( mac, ip); 
  //start UDP at 5000
  Udp.begin(localPort); 
  delay(1500);
  Serial.println(Ethernet.localIP());
 
}
 
void loop() {
  
  packetSize =Udp.parsePacket(); //Reads the packet size

  // if packetSize>0 means we have a request from client
  if(packetSize>0) { 

    //read data from packet buffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE); 
    //converting bytes to String
    
    String request(packetBuffer); 
    
    Serial.println(request);
    
    if (request =="A") {

      // Create a response packet for Client
      //i.e. Send Data to client
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.print(data); //Send the data
      Udp.endPacket(); //End the packet
      
    }
  }
  //clear packet buffer
  memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE); 
}
