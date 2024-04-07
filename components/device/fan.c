#include "device/fan.h"
#include "connection/mqtt.h"
#include <string.h>
#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"

Device_Vtable FAN_METHODS[] = {{ fan_set_state, device_response, fan_print }};

void fan_contructor(Fan* self, char* id,
        uint8_t gpio_pin, Device_State state, Fan_Level level) {

    device_constructor((Device*)self, id, gpio_pin, state);    
    self->base.methods = FAN_METHODS;
    strcpy(((Device*)self)->type, "fan");
    self->setLevel = &fan_set_level;
    self->level = level;
}

void fan_set_state(Device* self, Device_State state) {
    gpio_set_level(self->gpio_pin, state);
}

void fan_set_level(Fan* self, Fan_Level level) {
    self->level = level;
}

void fan_print(Device* self) {
    device_print(self);

    Fan* pFan = (Fan*)self;
    printf("level: %d\n", pFan->level);
}