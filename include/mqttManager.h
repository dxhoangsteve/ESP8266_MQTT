#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <CONFIG.h>

class MqttManager
{
public:
  MqttManager(const char *mqttServer, int mqttPort, const char *mqttUser = 0, const char *mqttPassword = 0);
  void connect( const char *mqttServer, int mqttPort);
  void publish(const char *topic, const char *message);
  void subscribe(const char *topic);
  void loop();
  bool isConnected();
  void reconnect();

private:
  WiFiClient _espClient;
  PubSubClient _client;
  const char *_mqttServer;
  int _mqttPort;
  const char *_mqttUser;
  const char *_mqttPassword;
};