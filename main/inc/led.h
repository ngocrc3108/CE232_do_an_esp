#ifndef __INC_LED_H__
#define __INC_LED_H__

#include "string.h"
#include "driver/gpio.h"
#include "../inc/query_string.h"
#include "stdio.h"
#include "mqtt_client.h"
#include "mqtt.h"

#define LED_ID "65fc0f92dc344fc0da52c6cb"
#define LED_GPIO 2

typedef enum {
    LED_STATE_OFF = 0,
    LED_STATE_ON = 1
} Led_State;

void ledInit();
void ledSetState(Led_State state);
extern void ledEventHandler(char *query);

#endif