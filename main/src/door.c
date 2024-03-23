#include "../inc/door.h"

static Door_State doorState;

void doorInit() {
    gpio_reset_pin(DOOR_GPIO);
    gpio_set_direction(DOOR_GPIO, GPIO_MODE_OUTPUT);

    //get level and state from database

    doorSetState(doorState);
}

void doorSetState(Door_State state) {
    doorState = state;
    gpio_set_level(DOOR_GPIO, state);
}

void doorEventHandler(char *query) {

}