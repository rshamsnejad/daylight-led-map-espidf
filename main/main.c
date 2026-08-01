#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "global.h"
#include "led_task.h"

#include "driver/gpio.h"
#define STRIP_GPIO GPIO_NUM_2

void app_main()
{
    led_strip_parameters_t strip_parameters = {
        .led_gpio = STRIP_GPIO
    };

    led_task_parameters_t led1_task_parameters = {
        .index = 0,
        .blink_time = 1000,
        .red = 255,
        .green = 255,
        .blue = 255
    };

    led_task_init(&strip_parameters);

    xTaskCreate(
        &led_task,      // task function
        "led_task", // task name
        2048,           // stack size in words
        &led1_task_parameters,  // pointer to parameters
        5,              // priority
        NULL);          // out pointer to task handle
}
