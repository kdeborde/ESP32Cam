#include "wifi_manager.h"
#include "credentials.h"
#include <WiFiUdp.h>

WiFiUDP udp;
const unsigned int udpPort = 6535;           // The port to send the UDP broadcast message to
const char *broadcastIp = "255.255.255.255"; // Broadcast IP address

// Connect to wifi with hardcoded credentials for now.
bool WifiManager::connect()
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
        // IPAddress static_ip(192, 168, 0, 13);
        // IPAddress gateway(192, 168, 0, 1);
        // IPAddress subnet(255, 255, 255, 0);
        // IPAddress dns(8, 8, 8, 8);
        // WiFi.config(static_ip, gateway, subnet, dns);
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

void WifiManager::sendBroadcastMessage()
{
    // Eventually use this mechanism for connectivity?
    String message = "Camera IP: " + WiFi.localIP().toString();
    message += "\nCamera MAC Address: " + WiFi.macAddress();
    udp.beginPacket(broadcastIp, udpPort);
    udp.write((const uint8_t *)message.c_str(), message.length());
    udp.endPacket();

    Serial.println("Broadcast message sent: " + message);
}