#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "led_strip.h"

#include "global.h"
#include "led_task.h"

#define RMT

void led_task_init(void)
{
    /// LED strip common configuration
    led_strip_config_t strip_config = {
        .strip_gpio_num = BLINK_GPIO,  // The GPIO that connected to the LED strip's data line
        .max_leds = 512,                 // The number of LEDs in the strip,
        .led_model = LED_MODEL_WS2812, // LED strip model, it determines the bit timing
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB, // The color component format is G-R-B
        .flags = {
            .invert_out = false, // don't invert the output signal
        }
    };

#ifdef RMT
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
    led_strip_handle_t led_strip = NULL;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
#else
    // SPI backend specific configuration
    led_strip_spi_config_t spi_config = {
        .clk_src = SPI_CLK_SRC_DEFAULT, // different clock source can lead to different power consumption
        .spi_bus = SPI2_HOST,           // SPI bus ID
        .flags = {
            .with_dma = true, // Using DMA can improve performance and help drive more LEDs
        }
    };

    /// Create the LED strip object
    ESP_ERROR_CHECK(led_strip_new_spi_device(&strip_config, &spi_config, &led_strip));
#endif
}

void led_task(void *pvParameter)
{

    led_strip_clear(led_strip);
    uint8_t on = 0;
    while(1){
        
        if(on){
            led_strip_set_pixel(led_strip, 1, 100, 100, 100);
        }
        else{
            led_strip_set_pixel(led_strip, 1, 1, 1, 1);
        }
        on = !on;

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}
