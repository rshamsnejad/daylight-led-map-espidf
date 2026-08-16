///////////////////////////////////////////////////////////
#ifndef SUN_MATH_H
#define SUN_MATH_H
///////////////////////////////////////////////////////////

#include <math.h>
#include <time.h>
#include "esp_err.h"

typedef struct sun_position_parameters_t
{
    double delta;
    double subsolar_lon;
} sun_position_parameters_t;


esp_err_t sun_position
(
    sun_position_parameters_t* return_struct,
    time_t* now
);

double degrees_to_radians
(
    double degrees
);

uint8_t is_daytime
(
    double lon,
    double lat,
    double delta,
    double lambda_s
);

///////////////////////////////////////////////////////////
#endif // SUN_MATH_H
///////////////////////////////////////////////////////////
