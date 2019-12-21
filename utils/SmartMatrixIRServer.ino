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

const char* kSsid = "ChangeThisToARealSSID";
const char* kPassword = "ChangeThisPasswordAsRequired";
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
                "<head><title> IR SmartMatrix Controller</title></head>" \
                "<body>" \
                  "<h1>SmartMatrix Aurora Web IR Controller Ready</h1>" \
                  "<p><a href=\"ir?code=378091719\">SMARTMATRIX_SELECT - Select - Send 0x168938C7</a></p>" \
                  "<p><a href=\"ir?code=378101919\">SMARTMATRIX_UP - Up - Send 0x1689609F</a></p>" \
                  "<p><a href=\"ir?code=378081519\">SMARTMATRIX_LEFT - Left - Send 0x168910EF</a></p>" \
                  "<p><a href=\"ir?code=378124359\">SMARTMATRIX_DOWN - Down - Send 0x1689B847</a></p>" \
                  "<p><a href=\"ir?code=378134559\">SMARTMATRIX_BRIGHTNESS_DOWN - BrightnessDown - Send 0x1689E01F</a></p>" \
                  "<p><a href=\"ir?code=378110079\">SMARTMATRIX_OVERLAY - CycleClockAndMessageFiles - Send 0x1689807F</a></p>" \
                  "<p><a href=\"ir?code=378126399\">SMARTMATRIX_PALETTE - Palette - Send 0x1689C03F</a></p>" \
                  "<p><a href=\"ir?code=378077439\">SMARTMATRIX_PLAY - PlayMode - Send 0x168900FF</a></p>" \
                  "<p><a href=\"ir?code=378130479\">SMARTMATRIX_POWER - Power - Send 0x1689D02F</a></p>" \
                  "<p><a href=\"ir?code=378132519\">SMARTMATRIX_BRIGHTNESS_UP - BrightnessUp - Send 0x1689D827</a></p>" \
                  "<p><a href=\"ir?code=378116199\">SMARTMATRIX_RIGHT - Right - Send 0x16899867</a></p>" \
                  "<p><a href=\"ir?code=378083559\">SMARTMATRIX_BACK - Back - Send 0x168918E7</a></p>" \
                  "<p><a href=\"ir?code=16621663\">ADAFRUIT_UP - Up - Send 0x00FDA05F</a></p>" \
                  "<p><a href=\"ir?code=16617583\">ADAFRUIT_ENTER_SAVE - Select - Send 0x00FD906F</a></p>" \
                  "<p><a href=\"ir?code=16613503\">ADAFRUIT_PLAY_PAUSE - Power - Send 0x00FD807F</a></p>" \
                  "<p><a href=\"ir?code=16609423\">ADAFRUIT_BACK - Back - Send 0x00FD708F</a></p>" \
                  "<p><a href=\"ir?code=16582903\">ADAFRUIT_1 - PlayMode - Send 0x00FD08F7</a></p>" \
                  "<p><a href=\"ir?code=16615543\">ADAFRUIT_2 - Palette - Send 0x00FD8877</a></p>" \
                  "<p><a href=\"ir?code=16599223\">ADAFRUIT_3 - CycleClockAndMessageFiles - Send 0x00FD48B7</a></p>" \
                  "<p><a href=\"ir?code=16591063\">ADAFRUIT_4 -  - Send 0x00FD28D7</a></p>" \
                  "<p><a href=\"ir?code=16580863\">ADAFRUIT_VOLUME_DOWN - BrightnessDown - Send 0x00FD00FF</a></p>" \
                  "<p><a href=\"ir?code=16623703\">ADAFRUIT_5 - ToggleSettingsMenuVisibility - Send 0x00FDA857</a></p>" \
                  "<p><a href=\"ir?code=16607383\">ADAFRUIT_6 - AudioScaleUp - Send 0x00FD6897</a></p>" \
                  "<p><a href=\"ir?code=16586983\">ADAFRUIT_7 - FreezeDisplay - Send 0x00FD18E7</a></p>" \
                  "<p><a href=\"ir?code=16619623\">ADAFRUIT_8 -  - Send 0x00FD9867</a></p>" \
                  "<p><a href=\"ir?code=16603303\">ADAFRUIT_9 - AudioScaleDown - Send 0x00FD58A7</a></p>" \
                  "<p><a href=\"ir?code=16601263\">ADAFRUIT_RIGHT - Right - Send 0x00FD50AF</a></p>" \
                  "<p><a href=\"ir?code=16584943\">ADAFRUIT_LEFT - Left - Send 0x00FD10EF</a></p>" \
                  "<p><a href=\"ir?code=16597183\">ADAFRUIT_VOLUME_UP - BrightnessUp - Send 0x00FD40BF</a></p>" \
                  "<p><a href=\"ir?code=16625743\">ADAFRUIT_DOWN - Down - Send 0x00FDB04F</a></p>" \
                  "<p><a href=\"ir?code=16589023\">ADAFRUIT_SETUP - Menu - Send 0x00FD20DF</a></p>" \
                  "<p><a href=\"ir?code=16605343\">ADAFRUIT_STOP_MODE -  - Send 0x00FD609F</a></p>" \
                  "<p><a href=\"ir?code=16593103\">ADAFRUIT_0_10_PLUS - ShowPatternName - Send 0x00FD30CF</a></p>" \
                  "<p><a href=\"ir?code=284106975\">SPARKFUN_SELECT - Select - Send 0x10EF20DF</a></p>" \
                  "<p><a href=\"ir?code=284162055\">SPARKFUN_A - PlayMode - Send 0x10EFF807</a></p>" \
                  "<p><a href=\"ir?code=284129415\">SPARKFUN_B - Palette - Send 0x10EF7887</a></p>" \
                  "<p><a href=\"ir?code=284121255\">SPARKFUN_C - CycleClockAndMessageFiles - Send 0x10EF58A7</a></p>" \
                  "<p><a href=\"ir?code=284153895\">SPARKFUN_POWER - CycleBrightness - Send 0x10EFD827</a></p>" \
                  "<p><a href=\"ir?code=284131455\">SPARKFUN_RIGHT - Right - Send 0x10EF807F</a></p>" \
                  "<p><a href=\"ir?code=284139615\">SPARKFUN_UP - Up - Send 0x10EFA05F</a></p>" \
                  "<p><a href=\"ir?code=284102895\">SPARKFUN_LEFT - Left - Send 0x10EF10EF</a></p>" \
                  "<p><a href=\"ir?code=284098815\">SPARKFUN_DOWN - Down - Send 0x10EF00FF</a></p>" \
                  "<p><a href=\"ir?code=16752735\">RONIX_SIX_BUTTON_UP - Up - Send 0x00FFA05F</a></p>" \
                  "<p><a href=\"ir?code=16716015\">RONIX_SIX_BUTTON_LEFT - Left - Send 0x00FF10EF</a></p>" \
                  "<p><a href=\"ir?code=16756815\">RONIX_SIX_BUTTON_DOWN - Down - Send 0x00FFB04F</a></p>" \
                  "<p><a href=\"ir?code=16732335\">RONIX_SIX_BUTTON_RIGHT - Right - Send 0x00FF50AF</a></p>" \
                  "<p><a href=\"ir?code=16748655\">RONIX_SIX_BUTTON_SELECT - Select - Send 0x00FF906F</a></p>" \
                  "<p><a href=\"ir?code=16728255\">RONIX_SIX_BUTTON_M -  - Send 0x00FF40BF</a></p>" \
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
