#include <stdio.h>
#include "device/device.h"
#include "device/fan.h"
#include "device/led.h"
#include "device/door.h"
#include "connection/wifi.h"
#include "connection/mqtt.h"
#include "esp_log.h"
#include <stdio.h>
#include "event_handler.h"

Fan fan;

void app_main(void) {
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }

    wifi_init_sta();
    mqtt_app_start();

    // always call contructors after initialize wifi, mqtt
    fan_contructor(&fan, "onlyfan", 2, 0, 0);
    Device* pDevice = (Device*)&fan;
    pDevice->methods->print(pDevice);
}