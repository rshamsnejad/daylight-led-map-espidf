///////////////////////////////////////////////////////////
#ifndef SUN_MATH_H
#define SUN_MATH_H
///////////////////////////////////////////////////////////

// Standard headers
#include <time.h>
// FreeRTOS headrs
//
// ESP-IDF headers
//
// ESP-IDF Component headers
//
// Custom headers
//

/// @brief Returns true if the sun is above the horizon at the given coordinates and time
/// @param longitude Longitude [-180°, 180°]
/// @param latitude Latitude [-90°, 90°]
/// @param timestamp Timestamp in seconds
/// @return true if day, false if night
bool is_daytime
(
    double longitude,
    double latitude,
    time_t timestamp
);

///////////////////////////////////////////////////////////
#endif // SUN_MATH_H
///////////////////////////////////////////////////////////
