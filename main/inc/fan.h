#ifndef __INC_FAN_H__
#define __INC_FAN_H__

#include "string.h"
#include "driver/gpio.h"
#include "driver/mcpwm.h"
#include "mqtt_client.h"
#include "esp_log.h"
#include "../inc/query_string.h"

#define FAN_ID "myfan"
#define FAN_GPIO 18

typedef enum {
    FAN_STATE_OFF = 0,
    FAN_STATE_ON = 1
} Fan_State;

typedef enum {
    FAN_LEVEL_LOW = 0,
    FAN_LEVEL_NORMAL = 1,
    FAN_LEVEL_HIGH = 2,
} Fan_Level;

void fanInit(); // (Ngoc)
void fanSetState(Fan_State state); // (Tung | Nguyen)
void fanSetLevel(Fan_Level level); // (Tung | Nguyen)
extern void fanEventHandler(char *query); // (Ngoc)

#endif