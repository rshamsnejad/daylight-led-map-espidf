// Standard headers
//
// FreeRTOS headers
#include "freertos/FreeRTOS.h"
// ESP-IDF headers
#include "esp_log.h"
#include "driver/gpio.h"
// ESP-IDF Component headers
#include <shiftregister_gpio.h>
// Custom headers
#include "global.h"
#include "date_clock.h"

void date_clock_init(void)
{
    /* configure GPIOs */
    date_clock_config.data_io_num = GPIO_NUM_6;
    date_clock_config.clk_io_num = GPIO_NUM_8;
    date_clock_config.rclk_io_num = GPIO_NUM_7;
    date_clock_config.srclr_io_num = GPIO_NUM_1;
    date_clock_config.oe_io_num = GPIO_NUM_3;
    date_clock_config.mode = SHIFTREGISTER_MODE_WRITE;

    ESP_ERROR_CHECK(shiftregister_gpio_init(&date_clock_config));
    ESP_LOGI(TAG, "Date clock initialized");
}

void date_clock_refresh(void)
{
    ESP_LOGI(TAG, "Refreshing date clock");

    uint8_t data[] = {0x0};
    size_t size = sizeof(data);

    for(;;){
    for(uint8_t i = 0 ; i <= 1 ; i += 1)
    {
        data[0] = LU_7segment[i];
        ESP_ERROR_CHECK(shiftregister_gpio_transfer(&date_clock_config, data, size));

        ESP_LOGI(TAG, "data = %d", data[0]);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }}
    // /* all pins == HIGH */
    // data[0] = 0xf;
    // ESP_ERROR_CHECK(shiftregister_gpio_transfer(&date_clock_config, data, size));

    // /* all pins == LOW */
    // data[0] = 0x0;
    // ESP_ERROR_CHECK(shiftregister_gpio_transfer(&date_clock_config, data, size));
    // vTaskDelay(1000);

    // /* last bit == HIGH */
    // data[0] = 0x1;
    // ESP_ERROR_CHECK(shiftregister_gpio_transfer(&date_clock_config, data, size));

    // for(int i = 0 ; i < 10 ; i += 1)
    // {
    //     vTaskDelay(1000);

    //     /* left-shift */
    //     data[0] = data[0] << 1;
    //     if (data[0] == 0) {
    //         data[0] = 0x1;
    //     }

    //     /* transfer */
    //     ESP_ERROR_CHECK(shiftregister_gpio_transfer(&date_clock_config, data, size));
    // }
    
    ESP_LOGI(TAG, "Date clock refreshed");
}