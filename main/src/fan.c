#include "../inc/fan.h"

#define FAN_MCPWM_UNIT MCPWM_UNIT_0
#define FAN_MCPWM_TIMER MCPWM_TIMER_0
#define FAN_MCPWM_GEN MCPWM_OPR_A

static Fan_State fanState;
static Fan_Level fanLevel;

void fanInit() {
    //Initialize MCPWM
    mcpwm_gpio_init(FAN_MCPWM_UNIT, MCPWM0A, FAN_GPIO);
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50;  // frequency = 50Hz
    pwm_config.cmpr_a = 0;        // duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;        // duty cycle of PWMxB = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, &pwm_config);

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
        mcpwm_set_duty(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, FAN_MCPWM_GEN, 0);
    }

} 
void fanSetLevel(Fan_Level level) {
    // (Tung | Nguyen)
    fanLevel = level;
    if (level == FAN_LEVEL_LOW)
    {
        mcpwm_set_duty(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, FAN_MCPWM_GEN, 50);
    }
    else if (level == FAN_LEVEL_NORMAL)
    {
        mcpwm_set_duty(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, FAN_MCPWM_GEN, 75);
    }
    else if (level == FAN_LEVEL_HIGH)
    {
        mcpwm_set_duty(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, FAN_MCPWM_GEN, 100);
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