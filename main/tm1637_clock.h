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

static tm1637_handle_t central_clock;
esp_err_t tm1637_clock_init(gpio_num_t CLK_pin, gpio_num_t DIO_pin);

typedef struct tm1637_clock_parameters_t
{
    tm1637_handle_t handle;
} tm1637_clock_parameters_t;

esp_err_t tm1637_refresh(void);

///////////////////////////////////////////////////////////
#endif // TM1637_CLOCK_H
///////////////////////////////////////////////////////////
