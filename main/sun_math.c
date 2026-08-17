// Standard headers
#include <math.h>
#include <time.h>
// FreeRTOS headers
//
// ESP-IDF headers
//
// ESP-IDF Component headers
#include <libnova/libnova.h>
// Custom headers
#include "sun_math.h"


bool is_daytime
(
    double longitude,
    double latitude,
    time_t timestamp
)
{
    struct ln_lnlat_posn observer = {
        .lng = longitude,
        .lat = latitude
    };

    struct ln_equ_posn sun_equatorial_position;
    struct ln_hrz_posn sun_horizontal_position;

    /* Convert Unix timestamp to Julian Day. */
    double julian_day = ln_get_julian_from_timet(&timestamp);

    /* Get Sun's apparent equatorial coordinates. */
    ln_get_solar_equ_coords(julian_day, &sun_equatorial_position);

    /* Convert equatorial coordinates to horizontal coordinates. */
    ln_get_hrz_from_equ(&sun_equatorial_position, &observer, julian_day, &sun_horizontal_position);

    /*
     * Sun altitude > 0 means the geometric center of the Sun
     * is above the mathematical horizon.
     */
    return sun_horizontal_position.alt > 0.0;
}

double degrees_to_radians
(
    double degrees
)
{
    return (degrees * (M_PI / 180.0));
}
