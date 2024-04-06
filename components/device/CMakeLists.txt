idf_component_register(SRCS "device.c" "fan.c"
                       INCLUDE_DIRS "include"
                       REQUIRES mqtt driver device)