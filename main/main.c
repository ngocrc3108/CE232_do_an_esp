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
Led led;

void app_main(void) {
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
    }

    fan_contructor(&fan, "65fc0fa8dc344fc0da52c6d1", 5, 0, 0);
    led_contructor(&led, "65fc0f92dc344fc0da52c6cb", 2, 0);
    wifi_init_sta();
    mqtt_init();
	eh_print_all_devices();
}