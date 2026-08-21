// Standard headers
#include <time.h>
// FreeRTOS headers
//
// ESP-IDF headers
#include "esp_err.h"
#include "esp_log.h"
// ESP-IDF Component headers
//
// Custom headers
#include "global.h"
#include "wifi_setup.h"
#include "local_time.h"

esp_err_t system_init(void)
{
    // Set local timezone
    // setenv("TZ", "Europe/Paris", 1);
    // For some reason "Europe/Paris" does not work but the actual TZ definition below works
    setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);
    tzset();

    esp_err_t error_code = ESP_OK;

    error_code =  wifi_init();
    if(error_code != ESP_OK)
        return error_code;

    error_code = timesync_init();
    if(error_code != ESP_OK)
        return error_code;

    time_t now_utc;
    struct tm now_local_time_tm;
    get_current_time(&now_utc, &now_local_time_tm);
    
    ESP_LOGI
    (
        TAG,
        "Local time at boot : %04d-%02d-%02d %02d:%02d:%02d",
        now_local_time_tm.tm_year + 1900,
        now_local_time_tm.tm_mon + 1,
        now_local_time_tm.tm_mday,
        now_local_time_tm.tm_hour,
        now_local_time_tm.tm_min,
        now_local_time_tm.tm_sec
    );

    return ESP_OK;
}