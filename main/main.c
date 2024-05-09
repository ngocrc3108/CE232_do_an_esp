#include <stdio.h>
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "./inc/mqtt.h"
#include "./inc/wifi.h"

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

    // fanSetState(FAN_STATE_ON);
    // while(1) {
        // fanSetLevel(FAN_LEVEL_LOW);
        // vTaskDelay(pdMS_TO_TICKS(3000)); // Hold for 3 second
        // fanSetLevel(FAN_LEVEL_NORMAL);
        // vTaskDelay(pdMS_TO_TICKS(3000)); // Hold for 3 second
        // fanSetLevel(FAN_LEVEL_HIGH);
        // vTaskDelay(pdMS_TO_TICKS(3000)); // Hold for 3 second
        // fanSetState(FAN_STATE_OFF);
        // vTaskDelay(pdMS_TO_TICKS(3000)); // Hold for 3 second

        // doorSetState(DOOR_STATE_OPEN);
        // vTaskDelay(pdMS_TO_TICKS(3000)); // Hold for 3 second
        // doorSetState(DOOR_STATE_CLOSE);
        // vTaskDelay(pdMS_TO_TICKS(3000)); // Hold for 3 second
    // }
}