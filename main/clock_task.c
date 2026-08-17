// Standard headers
#include <time.h>
// FreeRTOS headers
#include "freertos/FreeRTOS.h"
// ESP-IDF headers
#include "esp_log.h"
// ESP-IDF Component headers
#include "tm1637.h"
// Custom headers
#include "global.h"
#include "clock_task.h"
#include "local_time.h"

void clock_task_init(void *pvParameter)
{
    if(pvParameter){
        clock_task_init_parameters_t* args = (clock_task_init_parameters_t*) pvParameter;
    }
}

void clock_task(void *pvParameter)
{
    clock_task_parameters_t* args = (clock_task_parameters_t*)pvParameter;

    tm1637_config_t config = {
        .clk_pin = GPIO_NUM_4,
        .dio_pin = GPIO_NUM_5,
        .bit_delay_us = 100
    };
    tm1637_handle_t handle;
    tm1637_init(&config, &handle);
    tm1637_set_brightness(handle, 7, false);

    while(1)
    {
        time_t now_utc;
        time(&now_utc);
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
        // uint32_t delay_seconds = 5;

        ESP_LOGI(TAG, "Updating 7-segment clock...");

        tm1637_set_brightness(handle, 7, true);
        
        // Format: HH:MM (use colon segment if available)
        uint8_t time_display[4];
        time_display[0] = tm1637_encode_digit(now_local_tm.tm_hour / 10);
        time_display[1] = tm1637_encode_digit(now_local_tm.tm_hour % 10) | TM1637_SEG_DP;
        time_display[2] = tm1637_encode_digit(now_local_tm.tm_min / 10);
        time_display[3] = tm1637_encode_digit(now_local_tm.tm_min % 10);

        tm1637_set_segments(handle, time_display, 4, 0);
        
        ESP_LOGI(TAG, "CLOCK : %02d:%02d", now_local_tm.tm_hour, now_local_tm.tm_min);

        ESP_LOGI(TAG, "Waiting %d seconds until target time", delay_seconds);
        vTaskDelay(pdMS_TO_TICKS(delay_seconds * 1000));
    }
    // Clean up
    tm1637_deinit(handle);
}