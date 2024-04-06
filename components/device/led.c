#include "device/led.h"

Device_Vtable LED_METHODS[] = {{ led_set_state, device_response, device_print }};

void led_contructor(Led* self, const char* id, uint8_t gpio_pin, Device_State state) {
    device_constructor((Device*)self, id, gpio_pin, state);    
    self->base.methods = LED_METHODS;
}

void led_set_state(Device* self, Device_State state) {
    gpio_set_level(self->gpio_pin, state);
    self->state = state;
}