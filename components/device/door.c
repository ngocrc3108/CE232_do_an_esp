#include "device/door.h"
#include "connection/mqtt.h"
#include <string.h>
#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"

Device_Vtable DOOR_METHODS[] = {{ door_set_state, device_response, device_print }};

void door_contructor(Door* self, char* id, uint8_t gpio_pin, Device_State state) {
    device_constructor((Device*)self, id, gpio_pin, state);    
    self->base.methods = DOOR_METHODS;
    strcpy(((Device*)self)->type, "door");
}

void door_set_state(Device* self, Device_State state) {

}