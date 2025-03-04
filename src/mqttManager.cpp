#include <mqttManager.h>

void callback(char *topic, byte *payload, unsigned int length);

MqttManager::MqttManager(const char *mqttServer, int mqttPort, const char *mqttUser, const char *mqttPassword)
    : _client(_espClient), _mqttServer(mqttServer), _mqttPort(mqttPort), _mqttUser(mqttUser), _mqttPassword(mqttPassword)
{
}

void MqttManager::connect(const char *mqttServer, int mqttPort)
{
    _client.setServer(mqttServer, mqttPort);
    _client.setCallback(callback);
}

void MqttManager::publish(const char *topic, const char *message)
{
    _client.publish(topic, message);
}

void MqttManager::subscribe(const char *topic)
{
    _client.subscribe(topic);
}

void MqttManager::loop()
{
    _client.loop();
}

bool MqttManager::isConnected()
{
    return _client.connected();
}

void MqttManager::reconnect()
{
    while (!_client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (_client.connect("ESP8266"))
        {
            Serial.println("connected");
            _client.subscribe(SUB_TOPIC);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(_client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void callback(char *topic, byte *payload, unsigned int length)
{
    DynamicJsonDocument doc(221);
    deserializeJson(doc, payload, length);
    if (doc.containsKey("relay"))
    {
        if (doc["relay"] == "on")
        {
            digitalWrite(4, HIGH);
            Serial.println("Relay ON");
        }
        else
        {
            digitalWrite(4, LOW);
            Serial.println("Relay OFF");
        }
    }

    if (doc.containsKey("led"))
    {
        if (doc["led"] == "on")
        {
            digitalWrite(2, HIGH);
            Serial.println("LED ON");
        }
        else
        {
            digitalWrite(2, LOW);
            Serial.println("LED OFF");
        }
    }
}