#include "driver/gpio.h"

#define LED_RED GPIO_NUM_6
#define LED_GREEN GPIO_NUM_5
#define LED_BLUE GPIO_NUM_4

typedef struct led_task_parameters_t
{
    gpio_num_t led_gpio;
    TickType_t blink_time;
} led_task_parameters_t;

void led_task(void *pvParameter);