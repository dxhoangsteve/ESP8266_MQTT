#include <Arduino.h>
#include "WifiManager.h"
#include "mqttManager.h"
#include <CONFIG.h>
AsyncWebServer server(80);
MyWifiManager wifiManager(&server);
MqttManager mqttManager(MQTT_BROKER,MQTT_PORT);

void setup()
{
  wifiManager.connect();
  pinMode(RELAYPIN, OUTPUT);
  mqttManager.connect();
  mqttManager.subscribe(SUB_TOPIC);
  Serial.begin(115200);
}

void loop()
{
  if (wifiManager.isConnected())
  {
    if(mqttManager.isConnected())
    {
      mqttManager.loop();
    }
    else
    {
      mqttManager.reconnect();
    }
  }
  else
  {
    wifiManager.reConnect();
  }
}