// Standard headers
#include <stdlib.h>
#include <time.h>
// FreeRTOS headers
//
// ESP-IDF headers
//
// ESP-IDF Component headers
//
// Custom headers
#include "global.h"
#include "local_time.h"

void get_current_time(time_t* p_now_utc, struct tm* p_now_local_time_tm, uint8_t* p_date_clock_digits)
{
    time(p_now_utc);
    localtime_r(p_now_utc, p_now_local_time_tm);
    
    uint32_t year = p_now_local_time_tm->tm_year + 1900;
    p_date_clock_digits[0] = (uint8_t)(year / 1000);
    p_date_clock_digits[1] = (uint8_t)((year - (p_date_clock_digits[0] * 1000)) / 100);
    p_date_clock_digits[2] = (uint8_t)((year - (p_date_clock_digits[0] * 1000) - (p_date_clock_digits[1] * 100)) / 10);
    p_date_clock_digits[3] = (uint8_t)(year - (p_date_clock_digits[0] * 1000) - (p_date_clock_digits[1] * 100) - (p_date_clock_digits[2] * 10));
    p_date_clock_digits[4] = (uint8_t)(p_now_local_time_tm->tm_mon / 10);
    p_date_clock_digits[5] = (uint8_t)(p_now_local_time_tm->tm_mon - (p_date_clock_digits[4] * 10));
    p_date_clock_digits[6] = (uint8_t)(p_now_local_time_tm->tm_mday / 10);
    p_date_clock_digits[7] = (uint8_t)(p_now_local_time_tm->tm_mday - (p_date_clock_digits[6] * 10));  
}