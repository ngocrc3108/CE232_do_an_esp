#include "../inc/door.h"

static Door_State ledState;

void doorInit() {
    gpio_reset_pin(DOOR_GPIO);
    gpio_set_direction(DOOR_GPIO, GPIO_MODE_OUTPUT);

    //get level and state from database

    doorSetState(ledState);
}

void doorSetState(Door_State state) {
    ledState = state;
    gpio_set_level(DOOR_GPIO, state);
}

void doorEventHandler(char *query) {

}