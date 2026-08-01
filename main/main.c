#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED_RED GPIO_NUM_6
#define LED_GREEN GPIO_NUM_5
#define LED_BLUE GPIO_NUM_4

static const char *TAG = "example";
typedef struct led_task_parameters_t
{
    gpio_num_t led_gpio;
    TickType_t blink_time;
} led_task_parameters_t;

static led_task_parameters_t red_led_gpio = {LED_RED, 2000};
static led_task_parameters_t blue_led_gpio = {LED_BLUE, 1000};
static led_task_parameters_t green_led_gpio = {LED_GREEN, 500};

void led_task(void *pvParameter)
{
    gpio_num_t led_gpio = ((led_task_parameters_t *)pvParameter)->led_gpio;
    TickType_t blink_time = ((led_task_parameters_t *)pvParameter)->blink_time;
    uint8_t led_value = 0;
    gpio_reset_pin(led_gpio);
    gpio_set_direction(led_gpio, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(led_gpio, led_value);
        led_value = !led_value;

        ESP_LOGI(TAG, "GPIO %d = %d", led_gpio, led_value);
        vTaskDelay(blink_time / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void app_main()
{
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
