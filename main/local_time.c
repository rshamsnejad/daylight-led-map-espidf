#include <stdlib.h>
#include <time.h>
#include "local_time.h"

struct tm get_local_time(time_t now)
{
    struct tm now_local_tm;

    // Get current system time
    time(&now);
    // Set local timezone
    // setenv("TZ", "Europe/Paris", 1);
    setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);
    tzset();
    // Get localtime
    localtime_r(&now, &now_local_tm);

    return now_local_tm;
}