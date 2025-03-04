#include <Arduino.h>
#include "WifiManager.h"
#include "mqttManager.h"
#include <CONFIG.h>

AsyncWebServer server(80);
MyWifiManager wifiManager(&server);
MqttManager mqttManager(MQTT_BROKER, MQTT_PORT);

void setup()
{
  Serial.begin(115200);
  wifiManager.connect();
  pinMode(RELAYPIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);
  Serial.println("Connecting to MQTT...");
  Serial.printf("Broker: %s, Port: %d\n", MQTT_BROKER, MQTT_PORT);
  mqttManager.connect(MQTT_BROKER, MQTT_PORT);
  mqttManager.subscribe(SUB_TOPIC);
}

void loop()
{
  if (wifiManager.isConnected())
  {
    if (!mqttManager.isConnected())
      mqttManager.reconnect();
    mqttManager.loop();
  }
  else
  {
    wifiManager.reConnect();
  }
}