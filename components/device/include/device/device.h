#ifndef __DEVICE_H__
#define __DEVICE_H__


#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "connection/mqtt.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define DEVICE_ID_SIZE 24

typedef struct Device Device;
typedef struct Device_Vtable Device_Vtable;

typedef enum {
    DEVICE_STATE_OFF = 0,
    DEVICE_STATE_ON = 1
} Device_State;

struct Device_Vtable {
    void (*setState)(Device* self, Device_State state);
    void (*response)(Device* self, char* requestId, uint8_t success);
    void (*print)(Device* self);
};

struct Device {
    Device_Vtable* methods;
    char id[DEVICE_ID_SIZE];
    uint8_t gpio_pin;
    Device_State state;
};

extern void device_response(Device* self, char* requestId, uint8_t success);
extern void device_constructor(Device* self, const char* id, uint8_t gpio_pin, Device_State state);
extern void device_print(Device* self);
#endif