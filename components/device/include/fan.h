#ifndef __INC_FAN_H__
#define __INC_FAN_H__

#include "device.h"

#define FAN_ID "myfan"
#define FAN_GPIO 2

typedef struct Fan Fan;

typedef enum {
    FAN_LEVEL_LOW = 0,
    FAN_LEVEL_NORMAL = 1,
    FAN_LEVEL_HIGH = 2,
} Fan_Level;

struct Fan {
    Device base;
    void (*setLevel)(Fan* self, Fan_Level level);
    Fan_Level level;
};

extern void fan_contructor(Fan* self, const char* id,
        uint8_t gpio_pin, Device_State state, Fan_Level level);
extern void fan_set_level(Fan* self, Fan_Level level);
extern void fan_set_state(Device* self, Device_State state);

Device_Vtable FAN_METHODS[] = {{ fan_set_state, device_response }};

#endif