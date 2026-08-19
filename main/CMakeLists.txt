idf_component_register(
    SRCS            "DLM_task.c" "system_init.c" "local_time.c" "coord_math.c" "sun_math.c" "central_clock.c" "main.c" "led_matrix.c" "wifi_setup.c"
    INCLUDE_DIRS    "."
    REQUIRES        libnova
)
