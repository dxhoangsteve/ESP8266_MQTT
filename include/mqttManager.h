#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
class MqttManager
{
public:
  MqttManager(const char *mqttServer, int mqttPort, const char *mqttUser = "", const char *mqttPassword = "");
  void connect();
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