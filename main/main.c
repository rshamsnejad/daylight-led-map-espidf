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
#include "date_clock_task.h"

/// @brief Program entry point
/// This ESP32 firmware is for the Daylight LED Map (DLM),
/// a real-time physical map showing where it is day and night
/// on a PlateCarree map
void app_main()
{
    // Initializes the LED matrix, TM1637 clocks and 74HC595 clock
    ESP_ERROR_CHECK(peripherals_init());
    // Initializes the system components (Wifi, NTP etc)
    ESP_ERROR_CHECK(system_init());
    
    // The LED matrix does not need a dedicated task as it uses neopixels
    // The TM1637 clocks have their tasks started by the library
    // The 74HC595 clock needs its own task below
    xTaskCreate
    (
        &date_clock_task,
        "date_clock_task",
        2048,
        NULL,
        5,
        NULL
    );

    // Main task responsible for refreshing the displays
    xTaskCreate
    (
        &refresh_task,      // task function
        "refresh_task",     // task name
        2048,           // stack size in words
        NULL,           // pointer to parameters
        5,              // priority
        NULL
    );          // out pointer to task handle
}
