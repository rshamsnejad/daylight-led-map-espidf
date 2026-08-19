///////////////////////////////////////////////////////////
#ifndef HOURLY_TASK_H
#define HOURLY_TASK_H
///////////////////////////////////////////////////////////

// Standard headers
#include <time.h>
// FreeRTOS headers
#include "freertos/FreeRTOS.h"
// ESP-IDF headers
//
// ESP-IDF Component headers
//
// Custom headers
//

/// @brief Initializer for refresh_task()
/// @return ESP error code
esp_err_t refresh_task_init(void);

static TickType_t DLM_previous_wake_time;

/// @brief Main task responsible for refreshing the display
/// @param pvParameter Pointer to args
void refresh_task(void* pvParameter);

/// @brief Waits until system time reaches the desired time of day
/// @param target_tm The target time
void wait_until_target(struct tm target_tm);

///////////////////////////////////////////////////////////
#endif // HOURLY_TASK_H
///////////////////////////////////////////////////////////
