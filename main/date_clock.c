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
    for(uint8_t i = 0 ; i <= 15 ; i += 1)
    {
        data[0] = LU_7segment[i];
        ESP_ERROR_CHECK(shiftregister_gpio_transfer(&date_clock_config, data, size));

        ESP_LOGI(TAG, "data = %d (0x%X)", i, data[0]);
        vTaskDelay(pdMS_TO_TICKS(500));
    }}
    
    ESP_LOGI(TAG, "Date clock refreshed");
}