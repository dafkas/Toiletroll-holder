#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet2.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp2.h>
#include <Twitter.h>
#include <util.h>

//https://diyhacking.com/arduino-ldr-sensor/

#include <SPI.h>

// Unique MAC address to avoid conflicts with other devices on the network.
byte mac[] = {0x90, 0xA2, 0xDA, 0x10, 0xBF, 0xD1};

// Set the static IP address to use if the DHCP fails to assign.
IPAddress ip(192, 168, 0, 177);

// IP address of our target api.
IPAddress server(145,24,222,33);

// Library to use the ethernet shield.
EthernetClient client;

int sensorPin = A0;
int sensorValue = 0;
int led = 4;
String postData = "{test=marvin}";

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  Serial.println("s");
   if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");

    // DHCP failed so try establishinng connection with static ip.
    Ethernet.begin(mac, ip);
  }
  
}

void loop() {
  sensorValue = analogRead(sensorPin);
Serial.println(sensorValue);
  if(sensorValue > 500)
  {
    Serial.println("New Paper");
     Serial.println(sensorValue);
    digitalWrite(led, HIGH);
    if (client.connect(server, 80)) {
      Serial.println("connected with api!");
      Serial.println("sending POST request...");

      // The POST request for sending a new rating.
      client.println("GET http://145.24.222.33/smart-objects/changeRoll.php");
      client.println("Host:  145.24.222.234");
      client.println("User-Agent: Arduino/1.0");
      client.println("Connection: close");
      client.println("Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
      client.print("Content-Length: ");
      client.println(postData.length());
      client.println();
      client.println(postData);
      
      Serial.println("POST request sent!");
  } 
  else{
    digitalWrite(led, LOW);
  }
 
  }
}
