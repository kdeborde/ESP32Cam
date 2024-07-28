#include <Arduino.h>
#include <WiFi.h>
#include "img_converters.h"
#include "fb_gfx.h"
#include "web_server.h"
#define PART_BOUNDARY "123456789000000000000987654321"
static const char *_STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char *_STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char *_STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";

httpd_handle_t stream_httpd = NULL;

void web_server::start_camera_server()
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.server_port = 80;
    httpd_uri_t index_uri = {
        .uri = "/stream",
        .method = HTTP_GET,
        .handler = stream_handler,
        .user_ctx = NULL};
    if (httpd_start(&stream_httpd, &config) == ESP_OK)
    {
        Serial.println("Web Server Started at: " + WiFi.localIP().toString() + index_uri.uri);
        httpd_register_uri_handler(stream_httpd, &index_uri);
    }
}

esp_err_t web_server::stream_handler(httpd_req_t *req)
{
    camera_fb_t *frame_buf = NULL;
    esp_err_t response = ESP_OK;
    size_t _jpg_buf_len = 0;
    uint8_t *_jpg_buf = NULL;
    char *part_buf[64];

    response = httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
    if (response != ESP_OK)
    {
        return response;
    }

    while (true)
    {
        frame_buf = esp_camera_fb_get();
        if (!frame_buf)
        {
            Serial.println("Camera capture failed");
            response = ESP_FAIL;
        }
        else
        {
            if (frame_buf->width > 400)
            {
                if (frame_buf->format != PIXFORMAT_JPEG)
                {
                    bool jpeg_converted = frame2jpg(frame_buf, 80, &_jpg_buf, &_jpg_buf_len);
                    esp_camera_fb_return(frame_buf);
                    frame_buf = NULL;
                    if (!jpeg_converted)
                    {
                        Serial.println("JPEG compression failed");
                        response = ESP_FAIL;
                    }
                }
                else
                {
                    _jpg_buf_len = frame_buf->len;
                    _jpg_buf = frame_buf->buf;
                }
            }
        }

        // The repeated if's look strange but it makes sure each step completes successfully before continuing.
        if (response == ESP_OK)
        {
            size_t hlen = snprintf((char *)part_buf, 64, _STREAM_PART, _jpg_buf_len);
            response = httpd_resp_send_chunk(req, (const char *)part_buf, hlen);
        }
        if (response == ESP_OK)
        {
            response = httpd_resp_send_chunk(req, (const char *)_jpg_buf, _jpg_buf_len);
        }
        if (response == ESP_OK)
        {
            response = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY));
        }
        if (frame_buf)
        {
            esp_camera_fb_return(frame_buf);
            frame_buf = NULL;
            _jpg_buf = NULL;
        }
        else if (_jpg_buf)
        {
            free(_jpg_buf);
            _jpg_buf = NULL;
        }
        if (response != ESP_OK)
        {
            break;
        }
    }
    return response;
}