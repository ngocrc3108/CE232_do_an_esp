idf_component_register (
    SRCS "led.c" "fan.c" "door.c"
    INCLUDE_DIRS "include"
    REQUIRES mqtt driver connection query_string
)