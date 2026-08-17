///////////////////////////////////////////////////////////
#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H
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

/// @brief Initializer for the Wi-Fi connection
/// Currently uses example_connect() that the docs say to not use in production.
/// TODO : Look into doing it the right way (and maybe throw in a little web server for configuration)
/// @return ESP error code
esp_err_t wifi_init(void);

/// @brief Initializer for NTP sync
/// @return ESP error code
esp_err_t timesync_init(void);

///////////////////////////////////////////////////////////
#endif // WIFI_SETUP_H
///////////////////////////////////////////////////////////
