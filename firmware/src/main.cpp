#include <Arduino.h>
#include <WiFi.h>

#include "bell.h"

const uint8_t bellPin           = 13;
const char *ssid                = "EGGS";
const char *password            = "";

String request;

WiFiServer server(80);
Bell bell(bellPin);

void setup() {
  Serial.begin(115200);
  while (!Serial) {};

  WiFi.begin(ssid, password);
  WiFi.setHostname("prossecco-bell");

  Serial.println("main: Connect to wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("main: waiting for connection...");
  }
  Serial.println("main: Wifi connected!");
  Serial.println(WiFi.localIP());

  server.begin();
  bell.ding();
}

void loop() {
  WiFiClient client = server.available();

  if (!client) {
    return;
  }

  boolean currentLineIsBlank = true;

  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      request += c;
      Serial.write(c);

      if (c == '\n' && currentLineIsBlank) {
        if (request.indexOf("/ding") != -1)  {
          Serial.println("Ding!");
          bell.ding();
        }

        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();

        client.println("<html><p>Ding!</p></html>");

        break;
      }

      if(c == '\n') {
        currentLineIsBlank = true;
      } else if(c != '\r') {
        currentLineIsBlank = false;
      }
    }
  }
 
  delay(1);
  request = "";
  client.stop();
  Serial.println("Client disconnected");
}