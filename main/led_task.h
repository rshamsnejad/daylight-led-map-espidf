#include "driver/gpio.h"
#include "led_strip.h"

typedef struct led_task_parameters_t
{
    gpio_num_t led_gpio;
    TickType_t blink_time;
} led_task_parameters_t;

static led_strip_handle_t led_strip = NULL;

void led_task_init(void);
void led_task(void *pvParameter);