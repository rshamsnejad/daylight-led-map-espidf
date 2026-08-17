///////////////////////////////////////////////////////////
#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H
///////////////////////////////////////////////////////////

// Standard headers
//
// FreeRTOS headers
//
// ESP-IDF headers
#include "esp_err.h"
// ESP-IDF Component headers
//
// Custom headers
//


/// @brief Initializer for the required system parts
/// TODO : Look into a way to use the regular "Europe/Paris" type strings for defining the timezone
/// @return ESP error code
esp_err_t system_init(void);

///////////////////////////////////////////////////////////
#endif // SYSTEM_INIT_H
///////////////////////////////////////////////////////////
