#ifndef __DOOR_H__
#define __DOOR_H__

#include "device/device.h"

typedef struct Door Door;

struct Door {
    Device base;
};

void door_contructor(Door* self, char* id, uint8_t gpio_pin, Device_State state); // Ngoc
void door_set_state(Device* self, Device_State state); // Tung || Nguyen

#endif