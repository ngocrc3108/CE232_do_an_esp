#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "device/device.h"

#define EVENT_DEVICE_NUM_MAX 10

typedef enum {
    EVENT_HANDLE_FAIL = 0,
    EVENT_HANDLE_SUCCESS = 1
} Event_Handle_Status;

extern Event_Handle_Status event_handler_register_device(Device* device);
extern Event_Handle_Status event_handler_handle(char* topic, char* query_string);
Event_Handle_Status event_handler_on_set_state(Device* pDevice, char* query_string);
Event_Handle_Status event_handler_on_set_level(Device* pDevice, char* query_string);

#endif