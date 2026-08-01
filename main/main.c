#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "global.h"
#include "led_task.h"

#define LED_RED GPIO_NUM_6
#define LED_GREEN GPIO_NUM_5
#define LED_BLUE GPIO_NUM_4

void app_main()
{
    led_task_init();

    led_task_parameters_t red_led_gpio = {LED_RED, 2000};
    led_task_parameters_t blue_led_gpio = {LED_BLUE, 1000};
    led_task_parameters_t green_led_gpio = {LED_GREEN, 500};

    xTaskCreate(
        &led_task,      // task function
        "red_led_task", // task name
        2048,           // stack size in words
        &red_led_gpio,  // pointer to parameters
        5,              // priority
        NULL);          // out pointer to task handle

    xTaskCreate(
        &led_task,       // task function
        "blue_led_task", // task name
        2048,            // stack size in words
        &blue_led_gpio,  // pointer to parameters
        5,               // priority
        NULL);           // out pointer to task handle

    xTaskCreate(
        &led_task,        // task function
        "green_led_task", // task name
        2048,             // stack size in words
        &green_led_gpio,  // pointer to parameters
        5,                // priority
        NULL);            // out pointer to task handle
}
