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
#include "hourly_task.h"
#include "global.h"
#include "local_time.h"
#include "led_matrix.h"
#include "tm1637_clock.h"

esp_err_t hourly_task_init(void)
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

void hourly_task(void* pvParameter)
{
    ESP_LOGI(TAG, "Starting hourly_task()");

    while(true)
    {
        led_refresh();
        tm1637_refresh();

        wait_until_next_hour();
    }

    ESP_LOGI(TAG, "Exiting hourly_task()");
    vTaskDelete(NULL);
}

void wait_until_next_hour(void)
{
    time_t now_utc = time(NULL);
    struct tm now_local_tm = get_local_time(now_utc);

    // Target = Every hour o'clock
    struct tm target_tm = now_local_tm;
    target_tm.tm_min  = 0;
    target_tm.tm_sec  = 0;

    time_t target = mktime(&target_tm);

    // If o'clock has already passed, schedule next o'clock.
    if (target <= now_utc) {
        target_tm.tm_hour += 1;
        target = mktime(&target_tm);
    }
    uint32_t delay_seconds = (uint32_t)(target - now_utc);
    ESP_LOGI(TAG, "Waiting %d seconds until target time", delay_seconds);
    vTaskDelay(pdMS_TO_TICKS(delay_seconds * 1000));
}

void hourly_task_deinit(tm1637_handle_t central_clock)
{
    tm1637_deinit(central_clock);
}