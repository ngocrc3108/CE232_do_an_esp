#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

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

    //Initialize MCPWM
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, FAN_GPIO);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, DOOR_GPIO);
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50;  // frequency = 50Hz
    pwm_config.cmpr_a = 0;        // duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;        // duty cycle of PWMxB = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
  
    wifi_init_sta();
    mqtt_app_start();
    ledInit();
    fanInit();
}