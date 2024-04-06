#include "include/device.h"

void device_response(Device* self, char* requestId, uint8_t success) {
    char* buffer[50];
    sprintf(buffer, "requestId=%s&success=%d", requestId, success);
    //esp_mqtt_client_publish(mqtt_client, "response", buffer, 0, 2, 0);
}

extern void device_constructor(Device* self, const char* id, uint8_t gpio_pin, Device_State state) {
    strcpy(self->id, id);
    self->gpio_pin = gpio_pin;
    self->state = state;
}