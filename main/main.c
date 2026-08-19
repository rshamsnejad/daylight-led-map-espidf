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
#include "refresh_task.h"

/// @brief Program entry point
/// This ESP32 firmware is for the Daylight LED Map (DLM),
/// a real-time physical map showing where it is day and night
/// on a PlateCarree map
void app_main()
{
    ESP_ERROR_CHECK(refresh_task_init());
    ESP_ERROR_CHECK(system_init());
    
    xTaskCreate(
        &refresh_task,      // task function
        "refresh_task",     // task name
        2048,           // stack size in words
        NULL,           // pointer to parameters
        5,              // priority
        NULL);          // out pointer to task handle
}
