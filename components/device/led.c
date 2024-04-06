#include "device/led.h"
#include "connection/mqtt.h"
#include <string.h>
#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"

Device_Vtable LED_METHODS[] = {{ led_set_state, device_response, device_print }};

void led_contructor(Led* self, char* id, uint8_t gpio_pin, Device_State state) {
    device_constructor((Device*)self, id, gpio_pin, state);    
    self->base.methods = LED_METHODS;
}

void led_set_state(Device* self, Device_State state) {
    gpio_set_level(self->gpio_pin, state);
    self->state = state;
}