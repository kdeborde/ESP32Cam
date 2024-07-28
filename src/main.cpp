#include <Arduino.h>
#include "wifi_manager.h"
#include "camera_manager.h"
#include "web_server.h"

wifi_manager wifiManager;
camera_manager cameraManager;
web_server webServer;
unsigned long lastLedCheckTime = 0;
unsigned long ledCheckInterval = 3000;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_GPIO_NUM, OUTPUT);
  wifiManager.connect();

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20)
  {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (cameraManager.initialize_camera() == ESP_OK && WiFi.status() == WL_CONNECTED)
  {
    delay(1000);
    // TODO: Make sure this is successful.
    webServer.start_camera_server();
  }
  else
  {
    Serial.println("Failed to initialize camera.");
  }
}

void loop()
{
  if (!WiFi.isConnected())
  {
    for (int i = 0; i <= 255; i++)
    {
      ledcWrite(LEDC_CHANNEL_1, i);
      delay(10);
    }
    for (int i = 255; i > 0; i--)
    {
      ledcWrite(LEDC_CHANNEL_1, i);
      delay(10);
    }
    delay(200);
  }
  unsigned long currentTime = millis();
  if (currentTime - lastLedCheckTime >= ledCheckInterval)
  {
    wifiManager.send_broadcast_message();
  }
  lastLedCheckTime = currentTime;
}
