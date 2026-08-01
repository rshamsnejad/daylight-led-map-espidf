#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "led_strip.h"

#include "global.h"
#include "led_task.h"

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

    led_strip_clear(led_strip);
    led_task_parameters_t* args = (led_task_parameters_t*)pvParameter;

    uint8_t on = 0;

    while(1){
        if(on){

            // // Display Magenta => Yellow rainbow arc
            // int red = 0, green = 0, blue = 0;

            // for(int i = 0 ; i < 512 ; i += 1)
            // {
            //     if(i < 256)
            //     {
            //         red = 255;
            //         green = 0;
            //         blue = 255 - i;
            //     }
            //     else
            //     {
            //         red = 255;
            //         green = i - 256;
            //         blue = 0;
            //     }

            //     led_strip_set_pixel(led_strip, i, red, green, blue);
            // }
            
            // // Display black to white gradient
            // for(int i = 0 ; i < 512 ; i += 1)
            // {
            //     int j = i >= 256 ? i - 256 : i;

            //     led_strip_set_pixel(led_strip, i, j, j, j);
            // }

            // Display passed colors
            led_strip_set_pixel(led_strip, args->index, args->red, args->green, args->blue);
        }
        else{
            led_strip_clear(led_strip);
        }
        led_strip_refresh(led_strip);
        on = !on;

        vTaskDelay(args->blink_time / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}
