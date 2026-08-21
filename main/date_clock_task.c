// Standard headers
#include <time.h>
// FreeRTOS headers
#include "freertos/FreeRTOS.h"
// ESP-IDF headers
#include "esp_log.h"
// ESP-IDF Component headers
//
// Custom headers
#include "global.h"
#include "local_time.h"
#include "date_clock.h"
#include "date_clock_task.h"

void date_clock_task(void* pvParameters)
{
    uint32_t year = 0;
    uint8_t p_encoded_digit[] = { 0,0 };

    while(true)
    {
        for(uint8_t i = 0 ; i < p_date_clock_digits_size ; i += 1)
        {
            p_encoded_digit[0] = LU_7segment_digit[p_date_clock_digits[i]];
            p_encoded_digit[1] = LU_7segment_position[i];
            ESP_ERROR_CHECK(shiftregister_gpio_transfer(&date_clock_config, p_encoded_digit, sizeof(p_encoded_digit)));
            vTaskDelay(1);
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }

    vTaskDelete(NULL);
}