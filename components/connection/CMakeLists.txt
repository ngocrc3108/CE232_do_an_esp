idf_component_register(SRCS "wifi.c"
                       INCLUDE_DIRS "include"
                       REQUIRES mqtt esp_wifi nvs_flash)