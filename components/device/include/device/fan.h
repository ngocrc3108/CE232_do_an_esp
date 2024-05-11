#ifndef __INC_FAN_H__
#define __INC_FAN_H__

#include "string.h"
#include "driver/gpio.h"
#include "driver/mcpwm.h"
#include "mqtt_client.h"
#include "esp_log.h"
#include "query_string.h"
#include "connection/mqtt.h"

#define FAN_ID "6612c435e056da36ad2126a2"
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
void fanResponse(char* query, uint8_t success);
#endif