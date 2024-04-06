#include <stdio.h>
#include "device/device.h"
#include "device/fan.h"
#include "device/led.h"
#include "device/door.h"
#include "connection/wifi.h"
#include "connection/mqtt.h"

void app_main(void) {
    Fan fan;
    fan_contructor(&fan, "onlyfan", 5, 0, 0);
    Device* pDevice = (Device*)&fan;
    pDevice->methods->print(pDevice);
    Led led;
    led_contructor(&led, "myLed", 6, 0);
    pDevice = (Device*)&led;
    pDevice->methods->print(pDevice);
    Door door;
    door_contructor(&door, "myDoor", 7, 0);
    pDevice = (Device*)&door;
    pDevice->methods->print(pDevice);
}