#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

class WifiManager
{
private:
    /* data */
public:
    bool connect();
    void sendBroadcastMessage();
};

#endif