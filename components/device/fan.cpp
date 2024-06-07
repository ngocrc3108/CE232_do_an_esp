#include "device/fan.h"

#include "string.h"
#include "driver/gpio.h"
#include "driver/mcpwm.h"
#include "esp_log.h"

#include "query_string.h"
#include "connection/mqtt.h"

#define FAN_MCPWM_UNIT              MCPWM_UNIT_0
#define FAN_MCPWM_TIMER             MCPWM_TIMER_0
#define FAN_MCPWM_GEN               MCPWM_OPR_A
#define FAN_MCPWM_IO_SIGNAL         MCPWM0A

Fan::Fan(const char* id, gpio_num_t gpio_num) : Device(id, gpio_num) {
    //Initialize MCPWM
    mcpwm_gpio_init(FAN_MCPWM_UNIT, FAN_MCPWM_IO_SIGNAL, gpio_num);
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50;  // frequency = 50Hz
    pwm_config.cmpr_a = 0;        // duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;        // duty cycle of PWMxB = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, &pwm_config);

    level = FAN_LEVEL_LOW;
    sprintf(type_tring, "fan");
}

void Fan::setState(Device_state_t state) {
    this->state = state;

    if (state == DEVICE_STATE_ON) 
        setLevel(level);
    else if  (state == DEVICE_STATE_OFF)
        mcpwm_set_duty(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, FAN_MCPWM_GEN, 0);  
}

void Fan::setLevel(Fan_level_t level) {
    if(state == DEVICE_STATE_OFF)
        return;

    if (level == FAN_LEVEL_LOW)
        mcpwm_set_duty(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, FAN_MCPWM_GEN, 40);
    else if (level == FAN_LEVEL_NORMAL)
        mcpwm_set_duty(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, FAN_MCPWM_GEN, 55);
    else if (level == FAN_LEVEL_HIGH)
        mcpwm_set_duty(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, FAN_MCPWM_GEN, 100);
}

void Fan::eventHandler(char* query) {
    char cmd[10];
    getParameter(query, "cmd=", cmd);

    if(strcmp(cmd, "setState") == 0) {
        char state[10];
        getParameter(query, "state=", state);
        setState((Device_state_t)(state[0] - '0')); // state = '0' || '1'
        sendResponse(query, 1);
    } else if(strcmp(cmd, "setLevel") == 0) {
        char level[10];
        getParameter(query, "level=", level);
        setLevel((Fan_level_t)(level[0] - '0')); // level = '0' | '1' | '2'
        sendResponse(query, 1);
    } else if(strcmp(cmd, "sync") == 0) {
        char state[10];
        getParameter(query, "state=", state);
        setState((Device_state_t)(state[0] - '0')); // state = '0' || '1'

        char level[10];
        getParameter(query, "level=", level);
        setLevel((Fan_level_t)(level[0] - '0')); // level = '0' | '1' | '2'       
    }
}

void Fan::printInfo() {
    ESP_LOGI("INFO", "id: %s, type: %s, state: %d, level: %d", id, type_tring, state, level);
}