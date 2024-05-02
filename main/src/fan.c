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
    if (state == FAN_STATE_ON) 
    {
        fanSetLevel(fanLevel);
    }
    else if  (state == FAN_STATE_OFF)
    {
        gpio_set_level(FAN_GPIO, 0);
    }

} 
void fanSetLevel(Fan_Level level) {
    // (Tung | Nguyen)
    if (level == FAN_LEVEL_LOW)
    {
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 35);
    }
    else if (level == FAN_LEVEL_NORMAL)
    {
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 70);
    }
    else if (level == FAN_LEVEL_HIGH)
    {
        mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 100);
    }
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