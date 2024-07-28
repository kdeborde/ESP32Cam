#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

class wifi_manager
{
private:
    /* data */
public:
    bool connect();
    void send_broadcast_message();
};

#endif