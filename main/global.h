///////////////////////////////////////////////////////////
#ifndef GLOBAL_H
#define GLOBAL_H
///////////////////////////////////////////////////////////

#include <time.h>

#define BLINK_GPIO 2

#define MATRIX_WIDTH 32
#define MATRIX_HEIGHT 16
#define NUM_LEDS MATRIX_WIDTH*MATRIX_HEIGHT

#define LED_STRIP_PIN GPIO_NUM_2
#define CENTRALCLOCK_CLK_PIN GPIO_NUM_1
#define CENTRALCLOCK_DIO_PIN GPIO_NUM_0

#define DATECLOCK_DIO_PIN GPIO_NUM_5
#define DATECLOCK_SCLK_PIN GPIO_NUM_6
#define DATECLOCK_RCLK_PIN GPIO_NUM_7
#define DATECLOCK_SRCLR_PIN GPIO_NUM_4
#define DATECLOCK_OE_PIN GPIO_NUM_3

extern const char *TAG;

extern time_t now_utc;
extern struct tm now_local_time_tm;
extern struct tm next_minute_tm;
extern uint8_t p_date_clock_digits[];
extern size_t p_date_clock_digits_size;

///////////////////////////////////////////////////////////
#endif // GLOBAL_H
///////////////////////////////////////////////////////////
