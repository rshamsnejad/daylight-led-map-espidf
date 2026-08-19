// Standard headers
//
// FreeRTOS headers
//
// ESP-IDF headers
//
// ESP-IDF Component headers
#include <shiftregister_gpio.h>
// Custom headers
//

static shiftregister_config_t date_clock_config = {};

static const uint8_t LU_7segment[] =
{
    0b00000000,
    0b10000000,
    0b01000000,
    0b00100000,
    0b00010000,
    0b00001000,
    0b00000100,
    0b00000010,
    0b00000001
};
// {
//     0b00000000,
//     0b00100110,
//     0b11011010,
//     0b11110010,
//     0b01100110,
//     0b10110110,
//     0b10111110,
//     0b11100000,
//     0b11111110,
//     0b11110110,
//     0b11101110,
//     0b00111110,
//     0b10011100,
//     0b01111010,
//     0b10011110,
//     0b10001110
// };

void date_clock_init(void);

void date_clock_refresh(void);