#include "../inc/fan.h"

static Fan_State fanState;
static Fan_Level fanLevel;

void fanInit() {
    gpio_reset_pin(FAN_GPIO);
    gpio_set_direction(FAN_GPIO, GPIO_MODE_OUTPUT);

    //get level and state from database


    fanSetState(fanState);
    fanSetLevel(fanLevel);
}
void fanSetState(Fan_State state) {
    fanState = state;
    if(state) {
        // PWM by current level
    } else {
        // PWM = 0;
    }
}

void fanSetLevel(Fan_Level level) {
    fanLevel = level;

    if(fanState) {
        // PWM by level
    } // else do nothing
}