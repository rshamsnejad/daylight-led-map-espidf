///////////////////////////////////////////////////////////
#ifndef LED_TASK_H
#define LED_TASK_H
///////////////////////////////////////////////////////////

// Standard headers
//
// FreeRTOS headers
//
// ESP-IDF headers
#include "driver/gpio.h"
// ESP-IDF Component headers
#include "led_strip.h"
// Custom headers
//

typedef struct led_strip_parameters_t
{
    gpio_num_t led_gpio;
} led_strip_parameters_t;

typedef struct led_task_parameters_t
{
    uint32_t index;
    uint32_t red;
    uint32_t green;
    uint32_t blue;
    TickType_t blink_time;
} led_task_parameters_t;

static led_strip_handle_t led_strip = NULL;

void led_task_init(void *pvParameter);
void led_task(void *pvParameter);

///////////////////////////////////////////////////////////
#endif // LED_TASK_H
///////////////////////////////////////////////////////////
