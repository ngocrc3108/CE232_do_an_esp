#include <stdio.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "connection/mqtt.h"
#include "connection/wifi.h"

#include "device/led.h"
#include "device/fan.h"
#include "device/door.h"

void app_main(void)
{
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
  
    wifi_init_sta();
    mqtt_app_start();
    ledInit();
    fanInit();
    doorInit();
}