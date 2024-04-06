#include "device/door.h"

Device_Vtable DOOR_METHODS[] = {{ door_set_state, device_response, device_print }};

void door_contructor(Door* self, const char* id, uint8_t gpio_pin, Device_State state) {
    device_constructor((Device*)self, id, gpio_pin, state);    
    self->base.methods = DOOR_METHODS;
}

void door_set_state(Device* self, Device_State state) {

}