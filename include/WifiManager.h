#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include "CONFIG.h"
#include <ESP8266WiFi.h>
#include <ESPAsyncWiFiManager.h>
#include <DNSServer.h>

class MyWifiManager
{
public:
    MyWifiManager(AsyncWebServer *server);
    void connect();
    void reConnect();
    bool isConnected();

private:
    DNSServer dnsServer;
    AsyncWiFiManager wifiManager;
};

#endif