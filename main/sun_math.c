#include <math.h>
#include <time.h>

typedef struct sun_position_parameters_t
{
    double delta;
    double subsolar_lon;
} sun_position_parameters_t;


void sun_position(sun_position_parameters_t* return_struct, uint32_t utc_timestamp)
{
    time_t utc_time = time(utc_timestamp);
    struct tm* local_time = localtime(&utc_time);

    uint32_t N = local_time->tm_yday;
    double hour = local_time->tm_hour + local_time->tm_min / 60 + local_time->tm_sec / 3600;

    // Fractional year in radians
    double gamma = 2 * M_PI / 365 * (N - 1 + hour / 24);

    // Equation of Time (in minutes)
    double EoT = 229.18 * (
            0.000075
            + 0.001868 * cos(gamma)
            - 0.032077 * sin(gamma)
            - 0.014615 * cos(2 * gamma)
            - 0.040849 * sin(2 * gamma)
    );

    // Solar declination (in radians)
    double delta = (
        0.006918
        - 0.399912 * cos(gamma)
        + 0.070257 * sin(gamma)
        - 0.006758 * cos(2 * gamma)
        + 0.000907 * sin(2 * gamma)
        - 0.002697 * cos(3 * gamma)
        + 0.00148  * sin(3 * gamma)
    );

    // Subsolar longitude (in degrees [-180 , 180])
    double subsolar_lon = (180 - (hour * 15 + EoT * 0.25)) % 360 - 180

    return_struct->delta = delta;
    return_struct->subsolar_lon = subsolar_lon;
}

double degrees_to_radians(double degrees)
{
    return (degrees * (M_PI / 180.0))
}

uint8_t is_daytime(double lon, double lat, double delta, double lambda_s)
{
    double H = degrees_to_radians(lon - lambda_s);
    double cos_chi = sin(- lat) * sin(delta) + cos(- lat) * cos(delta) * cos(H)

    return cos_chi <= 0;
}