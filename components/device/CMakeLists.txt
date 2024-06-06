idf_component_register (
    SRCS "led.cpp" "fan.cpp" "door.cpp"
    INCLUDE_DIRS "include"
    REQUIRES mqtt driver connection query_string
)