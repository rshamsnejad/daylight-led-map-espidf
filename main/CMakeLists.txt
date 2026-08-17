idf_component_register(
    SRCS            "DLM_task.c" "system_init.c" "local_time.c" "neopixel_matrix.c" "sun_math.c" "tm1637_clock.c" "main.c" "led_matrix.c" "wifi_setup.c"
    INCLUDE_DIRS    "."
    REQUIRES        libnova
)
