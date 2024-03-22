#include "../inc/door.h"

static Door_State doorState;

void ledInit() {
    gpio_reset_pin(DOOR_GPIO);
    gpio_set_direction(DOOR_GPIO, GPIO_MODE_OUTPUT);

    //get level and state from database

    ledSetState(doorState);
}

void ledSetState(Door_State state) {
    doorState = state;
    gpio_set_level(DOOR_GPIO, state);
}