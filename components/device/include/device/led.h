#ifndef __LED_H__
#define __LED_H__

#include "device/device.h"

typedef struct Led Led;

struct Led {
    Device base;
    uint64_t time;
};

void led_contructor(Led* self, char* id, uint8_t gpio_pin, Device_State state);
void led_set_state(Device* self, Device_State state);

#endif