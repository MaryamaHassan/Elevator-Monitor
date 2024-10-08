#include <WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFiClient.h>
#include <Pushsafer.h>
#include <ArduinoJson.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <WiFiMulti.h>


Adafruit_LIS3DH lis = Adafruit_LIS3DH();


WiFiMulti wifiMulti;

char ssid[] = "Telia-2G-1A3327";        
char password[] = "Hassan123"; 
const char * hostDomain = "192.168.0.83"; //!!!
const int hostPort = 2002;

#define PushsaferKey "vexC3Qhk4E5GVpDmlO0N"
#define USE_SERIAL Serial

/*WiFiClientSecure client;*/
WiFiClient client;
Pushsafer pushsafer(PushsaferKey, client);


const int LED_PIN = LED_BUILTIN;

void connectToWiFi(const char * ssid, const char * pwd)
{
  Serial.println("Connecting to WiFi network: " + String(ssid));
  WiFi.begin(ssid, pwd); // start connecting to the wifi network

  while (WiFi.status() != WL_CONNECTED) 
  {
    // Blink LED while we're connecting:
    digitalWrite( LED_PIN, !digitalRead(LED_PIN) );
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void requestURL(const char * host, int port, int xValue, int yValue)
{
  Serial.println("Connecting to domain: " + String(host));

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port))
  {
    Serial.println("connection failed");
    return;
  }
  Serial.println("Connected!\n");

  // POST request to the server
  String dataToSendx ="X="+ String(xValue);
  String dataToSendy ="&Y="+ String(yValue);
  String dataToSend = dataToSendx + dataToSendy;

  int dataStringLength = dataToSend.length();
  client.print((String)"POST /api HTTP/1.1\r\n" +
               "Host: " + String(host) + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Content-Length: "+dataStringLength+"\r\n"+
               "Connection: close\r\n\r\n"+
               dataToSend);

//  timeout
  unsigned long timeout = millis();
  while (client.available() == 0)
  {
    if (millis() - timeout > 5000) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  while (client.available()) 
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  
  Serial.println("closing connection");
  client.stop();
}


void setup() {

  Serial.begin(115200);
  connectToWiFi(ssid, password);
  delay(4000);
  
  if (! lis.begin(0x18)) {   
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");

  lis.setRange(LIS3DH_RANGE_4_G);  

  lis.setDataRate(LIS3DH_DATARATE_50_HZ);


  pushsafer.debug = true;
}

void loop() {
  lis.read();    

  Serial.print("X:  "); Serial.print(lis.x);
  Serial.print("  \tY:  "); Serial.print(lis.y);
  Serial.print("  \tZ:  "); Serial.println(lis.z);

  // Records data when the x and y values are over 4000
  if (lis.x > 4000 || lis.y > 4000) {
    requestURL(hostDomain,hostPort, lis.x, lis.y);
    // Create a Pushsafer input struct with the desired notification parameters
    struct PushSaferInput input;
    input.message = "!Movments!";
    input.title = "Alert!";
    input.sound = "6";
    input.vibration = "1";
    input.icon = "1";
    input.iconcolor = "#ff8080";
    input.priority = "1";
    input.device = "a";

    // Send the notification using the Pushsafer library
    Serial.println(pushsafer.sendEvent(input));
    Serial.println("Sent");
  }

  delay(1000);
}
