#include <Ethernet.h> //Load Ethernet Library
#include <EthernetUdp.h> //Load the Udp Library
#include <SPI.h> //Load SPI Library
#include <WiFi101.h> //Load the Wi-Fi Library

char ssid[] = "mOOnRanger";        // network SSID (name)
//char pass[] = "password";    //  network password (Optional)

String data = "Wi-Fi tEAM rOCKs";
int status = WL_IDLE_STATUS;

//server(port)
WiFiServer server(200);

void setup() {
  //Feather M0 pin configuration
  WiFi.setPins(8, 7, 4, 2);

  //Start Access Point with name mOOnRanger(ssid)
  status = WiFi.beginAP(ssid);
  if (status != WL_AP_LISTENING) while (true);

  // wait 10 seconds for connection:
  delay(10000);

  // start the web server on port 200
  server.begin();
  //get the IP address and print it
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println(WiFi.SSID());
  
}

void loop() {
  // compare the previous status to the current status
  if (status != WiFi.status()) {
    // it has changed update the variable
    status = WiFi.status();
    Serial.println(status);
  }

  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,

    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
   
       //For reading bytes use read
       //For reading string use readString
       
       String data = client.readString(); 
       //Print data from Client
       Serial.println(data);
      }
      //Send data to Client
      server.write("Hello From Feather");
      delay(1000);
      
      
     }
    // close the connection if no client
    client.stop();

  }
}
