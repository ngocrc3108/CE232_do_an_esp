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

    // wifi_init_sta();
    // mqtt_app_start();

    // always call contructors after initialize wifi, mqtt
    fan_contructor(&fan, "onlyfan", 2, 0, 0);
    led_contructor(&led, "myLed", 5, 0);
	event_handler_print_all_devices();
	char buffer[1024];
	event_handler_get_all_device_id_and_type(buffer);
	printf(buffer);
}