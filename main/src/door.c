#include "../inc/door.h"

static Door_State ledState;

void doorInit() {
    gpio_reset_pin(DOOR_GPIO);
    gpio_set_direction(DOOR_GPIO, GPIO_MODE_OUTPUT);

    //TODO: get state from database (Ngoc)

    doorSetState(ledState);
}

void doorSetState(Door_State state) {
    // (Tung | Nguyen)
} 
extern void doorEventHandler(char *query) {
    // (Ngoc)
} 