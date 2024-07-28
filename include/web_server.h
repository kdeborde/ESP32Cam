#ifndef WEB_SERVER_H
#define WEB_SERVER_H
#include "esp_http_server.h"
class web_server
{
private:
    static esp_err_t stream_handler(httpd_req_t *req);

public:
    static void start_camera_server();
};

#endif
