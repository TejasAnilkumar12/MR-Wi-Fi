#include <Ethernet.h> //Load Ethernet Library
#include <EthernetUdp.h> //Load the Udp Library
#include <SPI.h> //Load SPI Library
#include "Wire.h"
#include <WiFi101.h>

String data;
char wifiDataBuff[50];

byte mac[] ={ 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE}; 
IPAddress ip(192, 168, 10, 243); 
unsigned int localPort = 5000; 
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
String request;
int packetSize; 
EthernetUDP Udp; 

char ssid[] = "MoonRanger";        // network SSID (name)
//char pass[] = "password";    //  network password (use for WPA, or use as key for WEP)


int status = WL_IDLE_STATUS;
WiFiServer server(200);

void setup() {
  WiFi.setPins(8, 7, 4, 2);
  status = WiFi.beginAP(ssid);
  if (status != WL_AP_LISTENING) while (true);
  // wait 10 seconds for connection:
  //delay(10000);
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  Ethernet.begin( mac, ip); 
  Udp.begin(localPort); 
 

  

  // start the web server on port 80
  server.begin();
  IPAddress wifiip = WiFi.localIP();
  Serial.print("Wifi IP Address: ");
  Serial.println(wifiip);
  Serial.print("Wifi SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("Ethernet IP: ");
  Serial.println(Ethernet.localIP());
  
 
}
 
void loop() {
  
  packetSize =Udp.parsePacket(); //Reads the packet size
  
  if(packetSize>0) { 
    
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE); 
    String request(packetBuffer); 
    Serial.println(request);
    if (request =="A") {
      data.toCharArray(wifiDataBuff,50);
      Serial.println(data);
//      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
//      Udp.print(data); //Send the temperature data
//      Udp.endPacket(); //End the packet
    
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,

    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
       String datafromClient = client.readString(); 
       //Serial.println(datafromClient);
      }
      
      server.write(wifiDataBuff);
      //Serial.write(server.write(sequence[i]));
      delay(1000);
   
     }
    // close the connection:
    client.stop();

  }
    }
    

      
  }
  memset(packetBuffer, 0, UDP_TX_PACKET_MAX_SIZE); 
}


void receiveEvent(int howMany)
{
  while(1 < Wire.available()) // loop through all but the last
  {
    data = Wire.readString(); // receive byte as a character
    //Serial.print(data);         // print the character
  }

}
