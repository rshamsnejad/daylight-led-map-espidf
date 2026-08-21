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
#include "local_time.h"

void date_clock_init(void)
{
    /* configure GPIOs */
    date_clock_config.data_io_num = DATECLOCK_DIO_PIN;
    date_clock_config.clk_io_num = DATECLOCK_SCLK_PIN;
    date_clock_config.rclk_io_num = DATECLOCK_RCLK_PIN;
    date_clock_config.srclr_io_num = DATECLOCK_SRCLR_PIN;
    date_clock_config.oe_io_num = DATECLOCK_OE_PIN;
    date_clock_config.mode = SHIFTREGISTER_MODE_WRITE;

    ESP_ERROR_CHECK(shiftregister_gpio_init(&date_clock_config));
    ESP_LOGI(TAG, "Date clock initialized");
}

void date_clock_refresh(void)
{
    ESP_LOGI(TAG, "Refreshing date clock");

    // uint8_t digit_code[] = { 0, 0 };

    // for(uint8_t i = 0 ; i <= 15 ; i += 1)
    // {
    //     digit_code[0] = LU_7segment_digit[i];
    //     digit_code[1] = LU_7segment_position[i % 8];
    //     ESP_ERROR_CHECK(shiftregister_gpio_transfer(&date_clock_config, digit_code, sizeof(digit_code)));

    //     ESP_LOGI(TAG, "digit_position = %d (0x%X)", digit_code[0], digit_code[0]);
    //     ESP_LOGI(TAG, "digit_code = %d (0x%X)", digit_code[1], digit_code[1]);
    //     vTaskDelay(pdMS_TO_TICKS(500));
    // }

    ESP_LOGI(TAG, "Date clock refreshed");
}