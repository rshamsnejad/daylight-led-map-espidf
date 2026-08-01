#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "global.h"
#include "clock_task.h"
#include "tm1637.h"

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
        tm1637_set_brightness(handle, 7, true);
        
        for(int i = 0 ; i <= 9999 ; i += 99)
        {
            tm1637_show_number(handle, i, false, 4, 0);
            ESP_LOGI(TAG, "CLOCK : %d", i);
            
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }
    // Clean up
    tm1637_deinit(handle);
}