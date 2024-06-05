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
#define FAN_MCPWM_IO_SIGNAL        MCPWM0A

static Fan_State fanState;
static Fan_Level fanLevel;

void fanInit() {
    //Initialize MCPWM
    mcpwm_gpio_init(FAN_MCPWM_UNIT, FAN_MCPWM_IO_SIGNAL, FAN_GPIO);
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 50;  // frequency = 50Hz
    pwm_config.cmpr_a = 0;        // duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;        // duty cycle of PWMxB = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    mcpwm_init(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, &pwm_config);

    //TODO: get level and state from database (Ngoc)
    fanState = FAN_STATE_OFF;
    fanLevel = FAN_LEVEL_LOW;

    fanSetState(fanState);
    fanSetLevel(fanLevel);
}

void fanSetState(Fan_State state) {
    // (Tung | Nguyen)
    fanState = state;

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

    if(fanState == FAN_STATE_OFF)
        return;

    if (level == FAN_LEVEL_LOW)
    {
        mcpwm_set_duty(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, FAN_MCPWM_GEN, 40);
    }
    else if (level == FAN_LEVEL_NORMAL)
    {
        mcpwm_set_duty(FAN_MCPWM_UNIT, FAN_MCPWM_TIMER, FAN_MCPWM_GEN, 55);
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
        if(strcmp(state, "1") == 0)
            fanSetState(FAN_STATE_ON);
        else if(strcmp(state, "0") == 0)
            fanSetState(FAN_STATE_OFF);
        ESP_LOGI("FAN", "set state: %s", state);
        fanResponse(query, 1);
    } else if(strcmp(cmd, "setLevel") == 0) {
        char level[10];
        getParameter(query, "level=", level);
        fanSetLevel((Fan_Level)(level[0] - '0')); // level = '0' | '1' | '2'
        ESP_LOGI("FAN", "set level: %s", level);
        fanResponse(query, 1);
    } else if(strcmp(cmd, "sync") == 0) {
        char state[10];
        getParameter(query, "state=", state);
        if(strcmp(state, "1") == 0)
            fanSetState(FAN_STATE_ON);
        else if(strcmp(state, "0") == 0)
            fanSetState(FAN_STATE_OFF);
        ESP_LOGI("FAN", "set state: %s", state);

        char level[10];
        getParameter(query, "level=", level);
        fanSetLevel((Fan_Level)(level[0] - '0')); // level = '0' | '1' | '2'
        ESP_LOGI("FAN", "set level: %s", level);                
    }

}

void fanResponse(char* query, uint8_t success) {
    char response[50];
    char requestId[20];
    getParameter(query, "requestId=", requestId);
    sprintf(response, "success=%d&requestId=%s", success, requestId);
    mqtt_publish("esp32/fan/response", response);
}

void fansendSyncRequest() {
    ESP_LOGI("DEBUG", "fan send sync request");
    char buffer[50];
    sprintf(buffer, "id=%s", FAN_ID);
    mqtt_publish("esp32/fan/sync", buffer);
}