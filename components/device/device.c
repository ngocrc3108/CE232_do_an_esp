#include "device/device.h"

void device_response(Device* self, char* requestId, uint8_t success) {
    char buffer[50];
    sprintf(buffer, "requestId=%s&success=%d", requestId, success);
    esp_mqtt_client_publish(mqtt_client, "response", buffer, 0, 2, 0);
}

void device_constructor(Device* self, const char* id, uint8_t gpio_pin, Device_State state) {
    strcpy(self->id, id);
    self->state = state;
    self->gpio_pin = gpio_pin;
    gpio_set_direction(gpio_pin, GPIO_MODE_OUTPUT);
}

void device_print(Device* self) {
    printf("id: %s\ngpio: %d\nstate: %d\n", self->id, self->gpio_pin, self->state);
}