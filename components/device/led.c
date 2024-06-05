#include "device/led.h"

#include "string.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "query_string.h"
#include "connection/mqtt.h"

static Led_State doorState;

void ledInit() {
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    // TODO: get state from database
    doorState = LED_STATE_OFF;

    ledSetState(doorState);
}

void ledSetState(Led_State state) {
    doorState = state;
    gpio_set_level(LED_GPIO, state);
}

void ledEventHandler(char *query) {
    char cmd[20];
    getParameter(query, "cmd=", cmd);
    if(strcmp(cmd, "setState") == 0) {
        char state[10];
        getParameter(query, "state=", state);
        if(strcmp(state, "1") == 0)
            ledSetState(LED_STATE_ON);
        else if(strcmp(state, "0") == 0)
            ledSetState(LED_STATE_OFF);
    
    ledResponse(query, 1);
    }
    if(strcmp(cmd, "sync") == 0) {
        char state[10];
        getParameter(query, "state=", state);
        if(strcmp(state, "1") == 0)
            ledSetState(LED_STATE_ON);
        else if(strcmp(state, "0") == 0)
            ledSetState(LED_STATE_OFF);    
    }
}

void ledResponse(char* query, uint8_t success) {
    char response[50];
    char requestId[20];

    if(getParameter(query, "requestId=", requestId) == GP_ERR)
        return;

    sprintf(response, "success=%d&requestId=%s", success, requestId);
    mqtt_publish("esp32/led/response", response); 
}

void ledsendSyncRequest() {
    ESP_LOGI("DEBUG", "led send sync request");
    char buffer[50];
    sprintf(buffer, "id=%s", LED_ID);
    mqtt_publish("esp32/led/sync", buffer);
}