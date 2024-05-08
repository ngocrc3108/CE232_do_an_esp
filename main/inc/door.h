#ifndef __INC_DOOR_H__
#define __INC_DOOR_H__

#include "string.h"
#include "driver/gpio.h"
#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

#define DOOR_ID "6612c42ee056da36ad21269f"
#define DOOR_GPIO 4

typedef enum {
    DOOR_STATE_CLOSE = 0,
    DOOR_STATE_OPEN = 1
} Door_State;

void doorInit(); // (Ngoc)
void doorSetState(Door_State state); // (Tung | Nguyen)
extern void doorEventHandler(char *query); // (Ngoc)

#endif