#include <time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "led_strip.h"

#include "global.h"
#include "led_task.h"
#include "neopixel_matrix.h"
#include "sun_math.h"

void led_task_init(void *pvParameter)
{
    /// LED strip common configuration
    led_strip_config_t strip_config = {
    .strip_gpio_num = ((led_strip_parameters_t*)pvParameter)->led_gpio,  // The GPIO that connected to the LED strip's data line
        .max_leds = 512,                 // The number of LEDs in the strip,
        .led_model = LED_MODEL_WS2812, // LED strip model, it determines the bit timing
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB, // The color component format is G-R-B
        .flags = {
            .invert_out = false, // don't invert the output signal
        }
    };

    /// RMT backend specific configuration
    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,    // different clock source can lead to different power consumption
        .resolution_hz = 10 * 1000 * 1000, // RMT counter clock frequency: 10MHz
        .mem_block_symbols = 64,           // the memory size of each RMT channel, in words (4 bytes)
        .flags = {
            .with_dma = false, // DMA feature is available on chips like ESP32-S3/P4
        }
    };

    /// Create the LED strip object
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
}

void led_task(void *pvParameter)
{
    while(1) {
        time_t now_utc;
        struct tm now_local_tm;
        struct tm target_tm;

        // Get current system time
        time(&now_utc);
        // Set local timezone
        // setenv("TZ", "Europe/Paris", 1);
        setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);
        tzset();
        // Get localtime
        localtime_r(&now_utc, &now_local_tm);

        ESP_LOGI(TAG, "Current system time : %04d-%02d-%02d %02d:%02d:%02d", now_local_tm.tm_year + 1900, now_local_tm.tm_mon + 1, now_local_tm.tm_mday, now_local_tm.tm_hour, now_local_tm.tm_min, now_local_tm.tm_sec);

        // Target = Every hour o'clock
        target_tm = now_local_tm;
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

        ESP_LOGI(TAG, "Waiting %d seconds until target time", delay_seconds);

        if(!INIT)
        {
            vTaskDelay(pdMS_TO_TICKS(delay_seconds * 1000));
        }

        ESP_LOGI(TAG, "Redrawing map...");

        led_task_parameters_t* args = (led_task_parameters_t*)pvParameter;

        xy_to_lonlat_args_t coords = {};
        xy_to_index_args_t  index = {};

        // Uncomment if flashing once on update is what you want
        // instead of a fast transition
        //
        //led_strip_clear(led_strip);
        for(uint32_t y = 0 ; y < MATRIX_HEIGHT ; y += 1)
        {
            for(uint32_t x = 0 ; x < MATRIX_WIDTH ; x += 1)
            {
                ESP_ERROR_CHECK(xy_to_lonlat(&coords, x, y, MATRIX_WIDTH, MATRIX_HEIGHT));
                ESP_ERROR_CHECK(xy_to_index(&index, x, y, MATRIX_WIDTH, MATRIX_HEIGHT, false, true, false, true, true));

                if(is_daytime(coords.longitude, coords.latitude, now_utc))
                {
                    led_strip_set_pixel(led_strip, index.index, 255, 249, 121);
                }
                else
                {
                    led_strip_set_pixel(led_strip, index.index, 81, 72, 178);
                }
                // ESP_LOGI(TAG, "(%d, %d) %d (%f N, %f E)", x, y, index.index, coords.latitude, coords.longitude);
            }
        }

        led_strip_refresh(led_strip);
        ESP_LOGI(TAG, "Map drawn.");
    }

    vTaskDelete(NULL);
}
