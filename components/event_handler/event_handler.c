#include "event_handler.h"
#include <stdint.h>
#include <string.h>
#include <esp_log.h>
#include "query_string.h"
#include "device/fan.h"

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

    ESP_LOGI(EVENT_HANDLER_LOG_TAG, "\ntopic: %s\nquery string: %s\n", topic, query_string);

    for(int i = 0; i < device_count; i++) {
        Device* pDevice = registed_devices[i];
        if(strcmp(pDevice->id, topic) == 0) {
            char cmd[20];
            query_string_get_value(query_string, "cmd=", cmd);\

            if(strcmp(cmd, "setState") == 0) 
                event_handler_on_set_state(pDevice, query_string);
            else if(strcmp(cmd, "setLevel") == 0) 
                event_handler_on_set_level(pDevice, query_string);
        }
    }
    return EVENT_HANDLE_FAIL;
}

Event_Handle_Status event_handler_on_set_state(Device* pDevice, char* query_string) {
    char state[10];
    query_string_get_value(query_string, "state=", state);
    Device_State deviceState = state[0] - '0'; // '0' | '1'
    pDevice->methods->setState(pDevice, deviceState);
    return EVENT_HANDLE_SUCCESS;
}

Event_Handle_Status event_handler_on_set_level(Device* pDevice, char* query_string) {
    char level[10];
    query_string_get_value(query_string, "level=", level);
    Fan_Level fanLevel = level[0] - '0'; // '0' | '1' | '2'
    ((Fan*)pDevice)->setLevel((Fan*)pDevice, fanLevel);
    return EVENT_HANDLE_SUCCESS;
}