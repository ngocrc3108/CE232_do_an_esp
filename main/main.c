#include <stdio.h>
#include "device/device.h"
#include "device/fan.h"
#include "device/led.h"
#include "connection/wifi.h"
#include "connection/mqtt.h"

void app_main(void) {
    Fan fan;
    fan_contructor(&fan, "onlyfan", 55, 0, 0);
    Device* pDevice = (Device*)&fan;
    pDevice->methods->print(pDevice);
    Led led;
    led_contructor(&led, "myLed", 44, 0);
    pDevice = (Device*)&led;
    pDevice->methods->print(pDevice);
}