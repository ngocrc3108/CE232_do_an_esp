#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <stdint.h>

#define DEVICE_ID_SIZE 24
#define DEVICE_LOG_TAG

typedef struct Device Device;
typedef struct Device_Vtable Device_Vtable;

typedef enum {
    DEVICE_STATE_OFF = 0,
    DEVICE_STATE_ON = 1
} Device_State;

struct Device_Vtable {
    void (*setState)(Device* self, Device_State state);
    void (*response)(Device* self, char* query_string, uint8_t success);
    void (*print)(Device* self);
};

struct Device {
    Device_Vtable* methods;
    char id[DEVICE_ID_SIZE];
    uint8_t gpio_pin;
    Device_State state;
    char type[5];
};

extern void device_response(Device* self, char* query_string, uint8_t success); // Ngoc
extern void device_constructor(Device* self, char* id, uint8_t gpio_pin, Device_State state); // Ngoc
extern void device_print(Device* self); // Ngoc. for debug
#endif