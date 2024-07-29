#ifndef WEB_SERVER_H
#define WEB_SERVER_H
#include "esp_http_server.h"
class CamWebServer
{
private:
    static esp_err_t streamHandler(httpd_req_t *req);
    static esp_err_t ledHandler(httpd_req_t *req);

public:
    static void startCameraServer();
};

#endif
