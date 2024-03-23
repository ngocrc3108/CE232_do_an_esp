#ifndef __INC_DOOR_H__
#define __INC_DOOR_H__

#include "string.h"
#include "driver/gpio.h"

#define DOOR_ID "abcd435435fdgdf"
#define DOOR_GPIO 2

typedef enum {
    DOOR_STATE_OFF = 0,
    DOOR_STATE_ON = 1
} Door_State;

void doorInit();
void doorSetState(Door_State state); 
extern void doorEventHandler(char *query);

#endif