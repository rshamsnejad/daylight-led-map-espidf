///////////////////////////////////////////////////////////
#ifndef TM1637_CLOCK_H
#define TM1637_CLOCK_H
///////////////////////////////////////////////////////////

// Standard headers
//
// FreeRTOS headers
//
// ESP-IDF headers
//
// ESP-IDF Component headers
#include "tm1637.h"
// Custom headers
//

/// @brief Global handle for the central clock module
static tm1637_handle_t central_clock;

/// @brief Initializer for the central clock module
/// @param CLK_pin
/// @param DIO_pin 
/// @return ESP error code
esp_err_t central_clock_init(gpio_num_t CLK_pin, gpio_num_t DIO_pin);

/// @brief Refreshes the central clock's display
/// @return ESP error code
esp_err_t tm1637_refresh(void);

///////////////////////////////////////////////////////////
#endif // TM1637_CLOCK_H
///////////////////////////////////////////////////////////
