// Standard headers
#include <time.h>
// FreeRTOS headers
//
// ESP-IDF headers
#include "esp_err.h"
#include "esp_log.h"
// ESP-IDF Component headers
//
// Custom headers
#include "DLM_task.h"
#include "global.h"
#include "local_time.h"
#include "led_matrix.h"
#include "tm1637_clock.h"

esp_err_t DLM_task_init(void)
{
    esp_err_t error_code = ESP_OK;

    led_strip_parameters_t strip_parameters =
    {
        .led_gpio = LED_STRIP_PIN
    };

    error_code = led_matrix_init(strip_parameters);
    if(error_code != ESP_OK)
        return error_code;

    error_code = tm1637_clock_init(CENTRALCLOCK_CLK_PIN, CENTRALCLOCK_DIO_PIN);
    if(error_code != ESP_OK)
        return error_code;

    tm1637_write_string(central_clock, "Hi !");

    return ESP_OK;
}

void DLM_task(void* pvParameter)
{
    ESP_LOGI(TAG, "Starting DLM_task()");

    struct tm next_minute;

    while(true)
    {
        tm1637_refresh();
        led_refresh();

        next_minute = get_local_time(time(NULL));
        next_minute.tm_sec = 0;
        next_minute.tm_min += 1;

        wait_until_target(next_minute);
    }

    ESP_LOGI(TAG, "Exiting DLM_task()");
    vTaskDelete(NULL);
}

void wait_until_target(struct tm target_tm)
{
    time_t now_utc = time(NULL);
    time_t target = mktime(&target_tm);

    if (target > now_utc)
    {
        uint32_t delay_seconds = (uint32_t)(target - now_utc);
        ESP_LOGI(TAG, "Waiting %d seconds until target time", delay_seconds);
        vTaskDelay(pdMS_TO_TICKS(delay_seconds * 1000));
    }
}
