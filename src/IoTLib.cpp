#include <IoTLib.hpp>

void IoTLib::setup()
{
 Serial.begin(9600);
 WiFiManager wifiManager;
 String apName = "provision-me-" + String(ESP.getChipId());
 Serial.println(apName);
 // id/name, placeholder/prompt, default, length
 WiFiManagerParameter fieldGateway("gateway", "field gateway", gatewayAddress, 40);
 wifiManager.addParameter(&fieldGateway);
 wifiManager.autoConnect(apName.c_str());
 // Comment line below and uncomment the autoconnect above to remember last settings
 //wifiManager.startConfigPortal(apName.c_str());
 strncpy(gatewayAddress, fieldGateway.getValue(), 40);
 //timeClient.begin();
}

const char* IoTLib::getGatewayAddress()
{
  return gatewayAddress;
}
