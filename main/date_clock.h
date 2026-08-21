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

static const uint8_t LU_7segment_digit[] =
{
    0b00000011, // 0 (0)
    0b10011111, // 1 (1)
    0b00100101, // 2 (2)
    0b00001101, // 3 (3)
    0b10011001, // 4 (4)
    0b01001001, // 5 (5)
    0b01000001, // 6 (6)
    0b00011111, // 7 (7)
    0b00000001, // 8 (8)
    0b00001001, // 9 (9)
    0b00010001, // A (10)
    0b11000001, // B (11)
    0b01100011, // C (12)
    0b10000101, // D (13)
    0b01100001, // E (14)
    0b01110001, // F (15)
};
static const uint8_t LU_7segment_position[] =
{
    0b00001000,
    0b00000100,
    0b00000010,
    0b00000001,
    0b10000000,
    0b01000000,
    0b00100000,
    0b00010000
};

static uint8_t date_clock_digits[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

void date_clock_init(void);

void date_clock_refresh(void);