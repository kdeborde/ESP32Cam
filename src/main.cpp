#include <Arduino.h>
#include "wifi_manager.h"
#include "camera_manager.h"
#include "web_server.h"

WifiManager wifiManager;
CameraManager cameraManager;
CamWebServer camWebServer;
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

  if (cameraManager.initializeCamera() == ESP_OK && WiFi.status() == WL_CONNECTED)
  {
    delay(1000);
    // TODO: Make sure this is successful.
    camWebServer.startCameraServer();
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
    wifiManager.sendBroadcastMessage();
  }
  lastLedCheckTime = currentTime;
}
