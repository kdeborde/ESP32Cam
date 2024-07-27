#include <Arduino.h>
#include "wifi_manager.h"

#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

wifi_manager wifiManager;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_GPIO_NUM, OUTPUT);
  wifiManager.devConnect();
}

void loop()
{
  // This is a sanity check to make sure code is actually uploaded.
  digitalWrite(LED_GPIO_NUM, HIGH);
  delay(3000);
  digitalWrite(LED_GPIO_NUM, LOW);
  delay(3000);
}
