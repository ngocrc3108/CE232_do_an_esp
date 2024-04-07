#include "device/device.h"
#include "connection/mqtt.h"
#include <string.h>
#include <stdio.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "event_handler.h"

char TAG[] = "DEVICE";

void device_response(Device* self, char* query_string, uint8_t success) {
    char buffer[70];
    sprintf(buffer, "%s&success=%d", query_string, success);
    int msg_id = esp_mqtt_client_publish(mqtt_client, "response", buffer, 0, 2, 0);
    ESP_LOGI(TAG, "sent response successful, msg_id=%d", msg_id);
}

void device_constructor(Device* self, char* id, uint8_t gpio_pin, Device_State state) {
    strcpy(self->id, id);
    self->state = state;
    self->gpio_pin = gpio_pin;
    gpio_set_direction(gpio_pin, GPIO_MODE_OUTPUT);

    event_handler_register_device(self);
    // int msg_id = esp_mqtt_client_subscribe(mqtt_client, id, 0);
    // ESP_LOGI(TAG, "sent subcribe successful, msg_id=%d", msg_id);
}

void device_print(Device* self) {
    printf("_ptr: %x\nid: %s\ntype: %s\ngpio: %d\nstate: %d\n",
        (int)self, self->id, self->type, self->gpio_pin, self->state);
}