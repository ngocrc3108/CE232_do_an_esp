#include "../inc/led.h"

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