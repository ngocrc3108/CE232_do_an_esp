#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>

#define LED_ID              "6612c416e056da36ad21269c"
#define LED_GPIO            5

typedef enum {
    LED_STATE_OFF = 0,
    LED_STATE_ON = 1
} Led_State;

void ledInit();
void ledSetState(Led_State state);
extern void ledEventHandler(char *query);
void ledResponse(char* query, uint8_t success);
#endif