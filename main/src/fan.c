#include "../inc/fan.h"

static Fan_State fanState;
static Fan_Level fanLevel;

void fanInit() {
    gpio_reset_pin(FAN_GPIO);
    gpio_set_direction(FAN_GPIO, GPIO_MODE_OUTPUT);

    //TODO: get level and state from database (Ngoc)

    fanSetState(fanState);
    fanSetLevel(fanLevel);
}

void fanSetState(Fan_State state) {
    // (Tung | Nguyen)
} 
void fanSetLevel(Fan_Level level) {
    // (Tung | Nguyen)
}

void fanEventHandler(char *query) {
    char cmd[10];
    getParameter(query, "cmd=", cmd);
    if(strcmp(cmd, "setState") ==0) {
        char state[10];
        getParameter(query, "state=", state);
        if(strcmp(state, "on"))
            fanSetState(FAN_STATE_ON);
        else if(strcmp(state, "off"))
            fanSetState(FAN_STATE_OFF);
        ESP_LOGI("FAN", "set state: %s", state);
    } else if(strcmp(cmd, "setLevel") == 0) {
        char level[10];
        getParameter(query, "level=", level);
        if(strcmp(level, "low") == 0)
            fanSetLevel(FAN_LEVEL_LOW);
        else if(strcmp(level, "normal") == 0)
            fanSetLevel(FAN_LEVEL_NORMAL);
        else if(strcmp(level, "high") == 0)
            fanSetLevel(FAN_LEVEL_HIGH);
        ESP_LOGI("FAN", "set level: %s", level);
    }
}