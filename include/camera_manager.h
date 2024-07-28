#include <Arduino.h>
#include "esp_camera.h"
#include "esp_timer.h"
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

class camera_manager
{
private:
public:
    static camera_config_t get_camera_config();
    static esp_err_t initialize_camera();
};
