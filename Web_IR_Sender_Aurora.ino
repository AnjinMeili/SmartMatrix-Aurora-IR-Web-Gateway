/*
 * SmartMatrix Aurora Web IR remote
 * Version 0.1 December, 2019  by James Hutchinson
 * 
 * Credit to Mark Szabo & David Conran for example esp8266 IR code.
 * 
 */
 
#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#endif  // ESP8266
#if defined(ESP32)
#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#endif  // ESP32
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <WiFiClient.h>

const char* kSsid = "SSIDofSomeOnesWiFi";
const char* kPassword = "PasswordForWifi";
MDNSResponder mdns;

#if defined(ESP8266)
ESP8266WebServer server(80);
#undef HOSTNAME
#define HOSTNAME "ir"
#endif  // ESP8266
#if defined(ESP32)
WebServer server(80);
#undef HOSTNAME
#define HOSTNAME "ir32"
#endif  // ESP32

const uint16_t kIrLed = 3;  // ESP GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

void handleRoot() {
    server.send(200, "text/html",
      "<html>" \
        "<head><title>Web SmartMatrix Aurora IR Controller</title></head>" \
        "<body>" \
          "<center>" \
            "<img src=\"https://camo.githubusercontent.com/f1da0c5a24842541b7bfbcd35571eb45af8ef246/687474703a2f2f646f63732e706978656c6d617469782e636f6d2f536d6172744d61747269782f70686f746f732f4f746865722f536d6172744d617472697852656d6f746547726170686963732e706e67\" usemap=\"#image-map\">" \
            "<map name=\"image-map\">" \
              "<area alt=\"Power\" title=\"Power\" href=\"ir?code=378130479\" coords=\"43,57,28\" shape=\"circle\">" \
              "<area alt=\"BrightDown\" title=\"BrightDown\" href=\"ir?code=378134559\" coords=\"102,58,27\" shape=\"circle\">" \
              "<area alt=\"BrightUp\" title=\"BrightUp\" href=\"ir?code=378132519\" coords=\"160,59,25\" shape=\"circle\">" \
              "<area alt=\"Play\" title=\"Play\" href=\"ir?code=378077439\" coords=\"43,109,24\" shape=\"circle\">" \
              "<area alt=\"Palette\" title=\"Palette\" href=\"ir?code=378126399\" coords=\"100,111,24\" shape=\"circle\">" \
              "<area alt=\"Overlay\" title=\"Overlay\" href=\"ir?code=378110079\" coords=\"158,112,25\" shape=\"circle\">" \
              "<area alt=\"Up\" title=\"Up\" href=\"ir?code=378101919\" coords=\"100,211,26\" shape=\"circle\">" \
              "<area alt=\"Left\" title=\"Left\" href=\"ir?code=378081519\" coords=\"42,270,25\" shape=\"circle\">" \
              "<area alt=\"Select\" title=\"Select\" href=\"ir?code=378091719\" coords=\"100,270,27\" shape=\"circle\">" \
              "<area alt=\"Right\" title=\"Right\" href=\"ir?code=378116199\" coords=\"160,267,27\" shape=\"circle\">" \
              "<area alt=\"Back\" title=\"Back\" href=\"ir?code=378083559\" coords=\"44,322,22\" shape=\"circle\">" \
              "<area alt=\"Down\" title=\"Down\" href=\"ir?code=378124359\" coords=\"101,327,25\" shape=\"circle\">" \
            "</map>" \
          "</center>" \
        "</body>" \
      "</html>");      
}

void handleIr() {
  for (uint8_t i = 0; i < server.args(); i++) {
    if (server.argName(i) == "code") {
      uint32_t code = strtoul(server.arg(i).c_str(), NULL, 10);
#if SEND_NEC
      irsend.sendNEC(code, 32);
#endif  // SEND_NEC
    }
  }
  handleRoot();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}

void setup(void) {
  irsend.begin();
  Serial.begin(115200,SERIAL_8N1,SERIAL_TX_ONLY);
  WiFi.begin(kSsid, kPassword);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

#if defined(ESP8266)
  if (mdns.begin(HOSTNAME, WiFi.localIP())) {
#else  // ESP8266
  if (mdns.begin(HOSTNAME)) {
#endif  // ESP8266
    //Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/ir", handleIr);
  
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);
  server.begin();
}

void loop(void) {
  server.handleClient();
}
