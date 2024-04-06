#include <stdio.h>
#include "device/device.h"
#include "connection/wifi.h"

void app_main(void) {
    Device d;
    device_constructor(&d, "my device", 55, 0);
    wifi_init_sta();
}