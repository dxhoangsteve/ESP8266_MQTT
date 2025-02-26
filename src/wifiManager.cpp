#include "WifiManager.h"
#include "CONFIG.h"
MyWifiManager::MyWifiManager(AsyncWebServer *server)
    : wifiManager(server, &dnsServer) {}

void MyWifiManager::connect()
{
    wifiManager.autoConnect("AutoConnectAP");
    isConnected();
}

void MyWifiManager::reConnect()
{
    if (!isConnected())
    {
        connect();
    }
}

bool MyWifiManager::isConnected()
{
    return WiFi.status();
}