idf_component_register(
    SRCS            "neopixel_matrix.c" "sun_math.c" "clock_task.c" "main.c" "led_task.c" "wifi_setup.c"
    INCLUDE_DIRS    "."
    REQUIRES        libnova
)
