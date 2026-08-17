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
#include "tm1637_clock.h"
#include "local_time.h"

esp_err_t central_clock_init(gpio_num_t CLK_pin, gpio_num_t DIO_pin)
{
    esp_err_t error_code = ESP_OK;
    
    tm1637_config_t config = {
        .clk_pin = CLK_pin,
        .dio_pin = DIO_pin,
        .bit_delay_us = 100
    };

    error_code = tm1637_init(&config, &central_clock);
    if(error_code != ESP_OK)
        return error_code;
    
    error_code = tm1637_set_brightness(central_clock, 7, true);
    if(error_code != ESP_OK)
        return error_code;
    
    tm1637_write_string(central_clock, " HI ");


    return ESP_OK;
}

esp_err_t tm1637_refresh(void)
{
    ESP_LOGI(TAG, "Updating 7-segment clock...");

    esp_err_t error_code = ESP_OK;
    
    error_code = tm1637_set_brightness(central_clock, 7, true);
    if(error_code != ESP_OK)
        return error_code;
    
    time_t now_utc = time(NULL);
    struct tm now_local_tm = get_local_time_struct(now_utc);
    
    // Format: HH:MM (use colon segment if available)
    uint8_t time_display[4];
    time_display[0] = tm1637_encode_digit(now_local_tm.tm_hour / 10);
    time_display[1] = tm1637_encode_digit(now_local_tm.tm_hour % 10) | TM1637_SEG_DP;
    time_display[2] = tm1637_encode_digit(now_local_tm.tm_min / 10);
    time_display[3] = tm1637_encode_digit(now_local_tm.tm_min % 10);

    error_code = tm1637_set_segments(central_clock, time_display, 4, 0);
    if(error_code != ESP_OK)
        return error_code;
    
    ESP_LOGI(TAG, "TM1637 updated to : %02d:%02d", now_local_tm.tm_hour, now_local_tm.tm_min);

    return ESP_OK;
}