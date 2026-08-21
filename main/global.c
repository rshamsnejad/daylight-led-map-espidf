// Standard headers
#include <time.h>
// FreeRTOS headers
//
// ESP-IDF headers
//
// ESP-IDF Component headers
//
// Custom headers
#include "global.h"

const char *TAG = "DLM_DBG";

time_t now_utc = 0;
struct tm now_local_time_tm = {0};
struct tm next_minute_tm = {0};
uint8_t p_date_clock_digits[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
size_t p_date_clock_digits_size = sizeof(p_date_clock_digits);