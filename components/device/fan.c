#include "include/fan.h"

void fan_contructor(Fan* self, const char* id,
        uint8_t gpio_pin, Device_State state, Fan_Level level) {

    device_constructor((Device*)self, id, gpio_pin, state);    
    self->base.methods = FAN_METHODS;
    self->setLevel = &fan_set_level;
    self->level = level;
}

void fan_set_state(Device* self, Device_State state) {
    gpio_set_level(self->gpio_pin, state);
}

void fan_set_level(Fan* self, Fan_Level level) {
    self->level = level;
}