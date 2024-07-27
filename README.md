Devices Used:

ESP32-CAM - https://www.amazon.com/dp/B09TB1GJ7P?ref=ppx_yo2ov_dt_b_product_details&th=1

FTDI Adapter - https://www.amazon.com/dp/B00IJXZQ7C?psc=1&ref=ppx_yo2ov_dt_b_product_details

Jumpers - https://www.amazon.com/dp/B01EV70C78?psc=1&ref=ppx_yo2ov_dt_b_product_details

Pin connections:
| ESP32-CAM | FTDI Adapter |
|-----------|--------------|
|    UOT    |      RX      |
|    UOR    |      TX      |
|    VCC    |      3V3     |
|    GND    |      GND     |

For Deployment/Upload, connect IO0 to GND on the ESP32-CAM and press the RST button.
When finished deploying, dissconnect the IO0 to GND pins and press RST button.


To connect to Wifi, copy credentials_template.h to credentials.h and update SSID and Password.

TODO's/Wishlist:

1. Switch to something for wifi connectivity other than hardcoded credentials. Initially connect over bluetooth and send creds?

2. Change from using static networking to DHCP and figure out how to broadcast it's address.
