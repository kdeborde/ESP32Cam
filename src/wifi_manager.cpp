#include "wifi_manager.h"
#include "credentials.h"

// Connect to wifi with hardcoded credentials.
bool wifi_manager::devConnect()
{
    WiFi.begin(ssid, password);

    // Wait for connection
    int attempts = 0;
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        IPAddress static_ip(192, 168, 0, 13);
        IPAddress gateway(192, 168, 0, 1);
        IPAddress subnet(255, 255, 255, 0);
        IPAddress dns(8, 8, 8, 8);
        WiFi.config(static_ip, gateway, subnet, dns);
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        return true;
    }
    else
    {
        Serial.println("");
        Serial.println("Failed to connect to WiFi");
        return false;
    }
}