#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "global.h"
#include "led_task.h"


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
