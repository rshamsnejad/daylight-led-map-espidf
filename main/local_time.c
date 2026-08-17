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
#include "local_time.h"

struct tm get_local_time_struct(time_t now)
{
    struct tm now_local_tm;

    // Get current system time
    time(&now);
    // Get localtime
    localtime_r(&now, &now_local_tm);

    return now_local_tm;
}