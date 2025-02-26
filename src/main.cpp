#include <Arduino.h>
#include "WifiManager.h"

AsyncWebServer server(80);
MyWifiManager wifiManager(&server);

void setup()
{
  wifiManager.connect();
  pinMode(RELAYPIN, OUTPUT);
}

void loop()
{
  if (wifiManager.isConnected())
  {
    digitalWrite(RELAYPIN, LOW);
    delay(1000);
  }
  else
  {
    digitalWrite(RELAYPIN, HIGH);
    wifiManager.reConnect();
    delay(1000);
  }
}