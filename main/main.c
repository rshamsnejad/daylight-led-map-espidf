// Standard headers
//
// FreeRTOS headers
#include "freertos/FreeRTOS.h"
// ESP-IDF headers
#include "esp_log.h"
#include "driver/gpio.h"
// ESP-IDF Component headers
//
// Custom headers
#include "global.h"
#include "system_init.h"
#include "DLM_task.h"

void app_main()
{
    ESP_ERROR_CHECK(system_init());
    
    ESP_ERROR_CHECK(DLM_task_init());
    xTaskCreate(
        &DLM_task,      // task function
        "DLM_task",     // task name
        2048,           // stack size in words
        NULL,           // pointer to parameters
        5,              // priority
        NULL);          // out pointer to task handle
}
