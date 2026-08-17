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

typedef struct led_strip_parameters_t
{
    gpio_num_t led_gpio;
} led_strip_parameters_t;

static led_strip_handle_t led_strip = NULL;

esp_err_t led_matrix_init(led_strip_parameters_t args);
void led_refresh(void);

///////////////////////////////////////////////////////////
#endif // LED_MATRIX_H
///////////////////////////////////////////////////////////
