#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include <Arduino.h>
#include "esp_camera.h"
#include "esp_timer.h"
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

class CameraManager
{
private:
public:
    static camera_config_t getCameraConfig();
    static esp_err_t initializeCamera();
};

#endif
