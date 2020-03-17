#include <WiFi.h>
const char* ssid     = "MoonRanger";


IPAddress server(192, 168, 1, 1); 

WiFiClient client;

void setup() {
  Serial.begin(9600);
Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid);


 while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  while(!client.connect(server, 200)){
    
Serial.print(".");
}
   Serial.println("Client Connected"); 
    client.println();}

void loop() {
  while (client.available()) {
    String data = client.readString();

   Serial.println(data);
  
   client.write("Hello from ESP32");
    // if the server's disconnected, stop the client:
    if (!client.connected()) {

      client.stop();

      // do nothing forevermore:
      while (true);
    }
  }
}
