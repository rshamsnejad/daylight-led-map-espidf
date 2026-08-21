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
#include "refresh_task.h"
#include "global.h"
#include "local_time.h"
#include "led_matrix.h"
#include "central_clock.h"
#include "date_clock.h"

esp_err_t peripherals_init(void)
{
    ESP_LOGI(TAG, "Starting peripherals_init()");
    esp_err_t error_code = ESP_OK;

    led_matrix_init_args_t strip_parameters =
    {
        .led_gpio = LED_STRIP_PIN
    };

    error_code = led_matrix_init(strip_parameters);
    if(error_code != ESP_OK)
        return error_code;

    error_code = central_clock_init(CENTRALCLOCK_CLK_PIN, CENTRALCLOCK_DIO_PIN);
    if(error_code != ESP_OK)
        return error_code;

    date_clock_init();

    ESP_LOGI(TAG, "Exiting peripherals_init()");
    return ESP_OK;
}

void refresh_task(void* pvParameter)
{
    ESP_LOGI(TAG, "Starting refresh_task()");

    time_t now_utc;
    struct tm now_local_time_tm;
    struct tm next_minute_tm;

    while(true)
    {
        get_current_time(&now_utc, &now_local_time_tm);

        next_minute_tm = now_local_time_tm;
        next_minute_tm.tm_sec = 0;
        next_minute_tm.tm_min += 1;
    
        tm1637_refresh();
        led_refresh();
        date_clock_refresh();

        wait_until_target(next_minute_tm);
    }

    ESP_LOGI(TAG, "Exiting refresh_task()");
    vTaskDelete(NULL);
}

void wait_until_target(struct tm target_tm)
{
    DLM_previous_wake_time = xTaskGetTickCount();

    time_t now_utc;
    struct tm now_local_time_tm;
    get_current_time(&now_utc, &now_local_time_tm);
    time_t target = mktime(&target_tm);

    if (target > now_utc)
    {
        uint32_t delay_seconds = (uint32_t)(target - now_utc);
        ESP_LOGI(TAG, "Waiting %d seconds until target time", delay_seconds);
        vTaskDelayUntil(&DLM_previous_wake_time, pdMS_TO_TICKS(delay_seconds * 1000));
    }
}
