#include "../inc/led.h"
#include "esp_log.h"

static Led_State ledState;

void ledInit() {
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    //get level and state from database

    ledSetState(ledState);
}

void ledSetState(Led_State state) {
    ledState = state;
    gpio_set_level(LED_GPIO, state);
}

void ledEventHandler(char *query) {
    char cmd[20];
    getParameter(query, "cmd=", cmd);
    if(strcmp(cmd, "setState") == 0) {
        char state[10];
        getParameter(query, "state=", state);
        if(strcmp(state, "on") == 0)
            ledSetState(LED_STATE_ON);
        else if(strcmp(state, "off") == 0)
            ledSetState(LED_STATE_OFF);
    esp_mqtt_client_subscribe(mqtt_client, "esp32/led", 0);
    char response[50];
    char requestId[20];
    getParameter(query, "requestId=", requestId);
    sprintf(response, "success=true&requestId=%s", requestId);
    esp_mqtt_client_publish(mqtt_client, "esp32/led", response, 0, 1, 0);
    }
}
