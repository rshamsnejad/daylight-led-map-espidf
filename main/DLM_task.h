///////////////////////////////////////////////////////////
#ifndef HOURLY_TASK_H
#define HOURLY_TASK_H
///////////////////////////////////////////////////////////

// Standard headers
#include <time.h>
// FreeRTOS headers
//
// ESP-IDF headers
//
// ESP-IDF Component headers
//
// Custom headers
//

/// @brief Initializer for DLM_task()
/// @return ESP error code
esp_err_t DLM_task_init(void);

/// @brief Main task responsible for refreshing the display
/// @param pvParameter Pointer to args
void DLM_task(void* pvParameter);

/// @brief Waits until system time reaches the desired time of day
/// @param target_tm The target time
void wait_until_target(struct tm target_tm);

///////////////////////////////////////////////////////////
#endif // HOURLY_TASK_H
///////////////////////////////////////////////////////////
