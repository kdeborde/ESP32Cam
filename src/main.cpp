#include <Arduino.h>
#include "wifi_manager.h"
#include "camera_manager.h"
#include "web_server.h"

wifi_manager wifiManager;
camera_manager cameraManager;
web_server webServer;

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
  // This is a sanity check to make sure code is actually uploaded.
  wifiManager.send_broadcast_message();
  digitalWrite(LED_GPIO_NUM, HIGH);
  delay(3000);
  digitalWrite(LED_GPIO_NUM, LOW);
  delay(3000);
}
