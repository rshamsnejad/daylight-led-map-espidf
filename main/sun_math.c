#include <math.h>
#include <time.h>

#include "esp_err.h"

#include "global.h"
#include "sun_math.h"

esp_err_t sun_position
(
    sun_position_parameters_t* return_struct,
    time_t* now
)
{
    time_t utc_time = time(now);
    struct tm* local_time = localtime(&utc_time);

    uint32_t N = local_time->tm_yday;
    double hour = local_time->tm_hour + local_time->tm_min / 60.0 + local_time->tm_sec / 3600.0;

    // Fractional year in radians
    double gamma = 2.0 * M_PI / 365.0 * (N - 1.0 + hour / 24.0);

    // Equation of Time (in minutes)
    double EoT =
        229.18 *
        (
            0.000075
            + 0.001868 * cos(gamma)
            - 0.032077 * sin(gamma)
            - 0.014615 * cos(2.0 * gamma)
            - 0.040849 * sin(2.0 * gamma)
        );

    // Solar declination (in radians)
    double delta =
        0.006918
        - 0.399912 * cos(gamma)
        + 0.070257 * sin(gamma)
        - 0.006758 * cos(2.0 * gamma)
        + 0.000907 * sin(2.0 * gamma)
        - 0.002697 * cos(3.0 * gamma)
        + 0.00148  * sin(3.0 * gamma);

    // Subsolar longitude (in degrees [-180 , 180])
    double subsolar_lon =
        fmod( (180.0 - (hour * 15.0 + EoT * 0.25)), 360.0) - 180.0;

    return_struct->delta = delta;
    return_struct->subsolar_lon = subsolar_lon;

    return ESP_OK;
}

double degrees_to_radians
(
    double degrees
)
{
    return (degrees * (M_PI / 180.0));
}

uint8_t is_daytime
(
    double lon,
    double lat,
    double delta,
    double lambda_s
)
{
    double H = degrees_to_radians(lon - lambda_s);
    double cos_chi = sin(- lat) * sin(delta) + cos(- lat) * cos(delta) * cos(H);

    return cos_chi <= 0;
}