#ifndef __EVENT_HANDLER_H__
#define __EVENT_HANDLER_H__

#include "device/device.h"

#define EVENT_DEVICE_NUM_MAX 10

typedef enum {
    EVENT_HANDLE_FAIL = 0,
    EVENT_HANDLE_SUCCESS = 1
} Event_Handle_Status;

extern Event_Handle_Status eh_register_device(Device* device);
extern Event_Handle_Status eh_subscribe_devices();
Event_Handle_Status eh_get_all_device_id_and_type(char* result);
extern Event_Handle_Status eh_on_message(char* topic, char* query_string);
Event_Handle_Status eh_set_state(Device* pDevice, char* query_string);
Event_Handle_Status eh_set_level(Device* pDevice, char* query_string);
extern Event_Handle_Status eh_print_all_devices(); // for debug
#endif