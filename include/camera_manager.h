#include <Arduino.h>
#include <WiFi.h>
#include "esp_camera.h"
#include "esp_timer.h"
#include "img_converters.h"
#include "fb_gfx.h"
#include "esp_http_server.h"
#define PART_BOUNDARY "123456789000000000000987654321"
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

class camera_manager
{
private:
public:
    static camera_config_t get_camera_config();
    static esp_err_t initialize_camera();
    static void startCameraServer();
};
