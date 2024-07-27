#include <Arduino.h>
#include "wifi_manager.h"
#include "camera_manager.h"

wifi_manager wifiManager;
camera_manager cameraManager;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_GPIO_NUM, OUTPUT);
  wifiManager.devConnect();

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
    cameraManager.startCameraServer();
  }
  else
  {
    Serial.println("Failed to initialize camera.");
  }
}

void loop()
{
  // This is a sanity check to make sure code is actually uploaded.
  digitalWrite(LED_GPIO_NUM, HIGH);
  delay(3000);
  digitalWrite(LED_GPIO_NUM, LOW);
  delay(3000);
}
