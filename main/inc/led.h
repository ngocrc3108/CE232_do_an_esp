#ifndef __INC_LED_H__
#define __INC_LED_H__

#include "string.h"
#include "driver/gpio.h"

#define LED_ID "abcd435435fdgdf"
#define LED_GPIO 2

typedef enum {
    LED_STATE_OFF = 0,
    LED_STATE_ON = 1
} Led_State;

void ledInit();
void ledSetState(Led_State state); 

#endif