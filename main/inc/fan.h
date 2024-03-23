#ifndef __INC_FAN_H__
#define __INC_FAN_H__

#include "string.h"
#include "driver/gpio.h"
#include "../inc/query_string.h"

#define FAN_ID "myfan"
#define FAN_GPIO 2

typedef enum {
    FAN_STATE_OFF = 0,
    FAN_STATE_ON = 1
} Fan_State;

typedef enum {
    FAN_LEVEL_LOW = 0,
    FAN_LEVEL_NORMAL = 1,
    FAN_LEVEL_HIGH = 2,
} Fan_Level;

void fanInit();
void fanSetState(Fan_State state);
void fanSetLevel(Fan_Level level);
extern void fanEventHandler(char *query);

#endif