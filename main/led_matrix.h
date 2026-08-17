///////////////////////////////////////////////////////////
#ifndef LED_MATRIX_H
#define LED_MATRIX_H
///////////////////////////////////////////////////////////

// Standard headers
//
// FreeRTOS headers
#include "freertos/FreeRTOS.h"
// ESP-IDF headers
#include "driver/gpio.h"
#include "esp_err.h"
// ESP-IDF Component headers
#include "led_strip.h"
// Custom headers
//


/// @brief Input parameters for led_matrix_init()
/// @param led_gpio Data pin of the neopixel strip
typedef struct led_matrix_init_args_t
{
    gpio_num_t led_gpio;
} led_matrix_init_args_t;

/// @brief Global handle for the LED matrix
static led_strip_handle_t led_strip = NULL;

/// @brief Initializer for the LED matrix
/// @param args 
/// @return ESP error code
esp_err_t led_matrix_init(led_matrix_init_args_t args);

/// @brief Refreshes the LED map to update to the current time
void led_refresh(void);

///////////////////////////////////////////////////////////
#endif // LED_MATRIX_H
///////////////////////////////////////////////////////////
