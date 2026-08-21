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

void get_current_time(time_t* p_now_utc, struct tm* p_now_local_time_tm)
{
    time(p_now_utc);
    localtime_r(p_now_utc, p_now_local_time_tm);
}