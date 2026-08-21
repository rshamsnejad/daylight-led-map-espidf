// Standard headers
#include <time.h>
// FreeRTOS headers
#include "freertos/FreeRTOS.h"
// ESP-IDF headers
#include "esp_log.h"
// ESP-IDF Component headers
#include "led_strip.h"
// Custom headers
#include "global.h"
#include "led_matrix.h"
#include "coord_math.h"
#include "sun_math.h"
#include "local_time.h"

esp_err_t led_matrix_init(led_matrix_init_args_t args)
{
    /// LED strip common configuration
    led_strip_config_t strip_config = {
    .strip_gpio_num = args.led_gpio,  // The GPIO that connected to the LED strip's data line
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
    esp_err_t error_code = led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip);

    return error_code;
}

void led_refresh(void)
{
    ESP_LOGI(TAG, "Redrawing LED map...");

    time_t now_utc;
    struct tm now_local_time_tm;
    get_current_time(&now_utc, &now_local_time_tm);

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
    ESP_LOGI(TAG, "LED map redrawn.");
}
