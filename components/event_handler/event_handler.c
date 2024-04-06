#include "event_handler.h"
#include <stdint.h>
#include <string.h>

Device* registed_devices[EVENT_DEVICE_NUM_MAX];
int device_count = 0;

Event_Handle_Status event_handler_register_device(Device* device) {
    if(device_count >= EVENT_DEVICE_NUM_MAX - 1)
        return EVENT_HANDLE_FAIL;
    registed_devices[device_count] = device;
    device_count++;
    return EVENT_HANDLE_SUCCESS;
}

Event_Handle_Status event_handler_handle(char* topic, char* query_string) {
    for(int i = 0; i < device_count; i++) {
        if(strcmp(registed_devices[i]->id, topic) == 0) {
            char cmd[10];
        }
    }
    return EVENT_HANDLE_FAIL;
}