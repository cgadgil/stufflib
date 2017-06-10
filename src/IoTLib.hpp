#include <stdint.h>
//Library allows either I2C or SPI, so include both.
#include "Wire.h"
#include "SPI.h"
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "0.pool.ntp.org"

class IoTLib {
  WiFiUDP ntpUDP;
  NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);
  char gatewayAddress[40];

public:
  void setup() {
    Serial.begin(9600);
    WiFiManager wifiManager;
    String apName = "provision-me-" + String(ESP.getChipId());
    Serial.println(apName);
    // id/name, placeholder/prompt, default, length
    WiFiManagerParameter fieldGateway("gateway", "field gateway", gatewayAddress, 40);
    wifiManager.addParameter(&fieldGateway);
    //wifiManager.autoConnect(apName.c_str());
    // Comment line below and uncomment the autoconnect above to remember last settings
    wifiManager.startConfigPortal(apName.c_str());
    strncpy(gatewayAddress, fieldGateway.getValue(), 40);
    timeClient.begin();
  }
}
