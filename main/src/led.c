#include "../inc/led.h"
#include "esp_log.h"

static Led_State doorState;

void ledInit() {
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    //get level and state from database

    ledSetState(doorState);
}

void ledSetState(Led_State state) {
    doorState = state;
    gpio_set_level(LED_GPIO, state);
}

void ledEventHandler(char *query) {
    char cmd[20];
    getParameter(query, "cmd=", cmd);
    if(strcmp(cmd, "setState") == 0) {
        char state[10];
        getParameter(query, "state=", state);
        if(strcmp(state, "on") == 0)
            ledSetState(LED_STATE_ON);
        else if(strcmp(state, "off") == 0)
            ledSetState(LED_STATE_OFF);
    }
}
