///////////////////////////////////////////////////////////
#ifndef NEOPIXEL_MATRIX_H
#define NEOPIXEL_MATRIX_H
///////////////////////////////////////////////////////////

#include "esp_err.h"
#include "global.h"

typedef struct xy_to_index_args_t
{
    uint32_t index;
} xy_to_index_args_t;

esp_err_t xy_to_index
(
    xy_to_index_args_t* return_struct,
    uint32_t            x,
    uint32_t            y,
    uint32_t            width,
    uint32_t            height,
    BOOL_T              zigzag,
    BOOL_T              row_major,
    BOOL_T              flip_x,
    BOOL_T              flip_y,
    BOOL_T              square_split_x
);

typedef struct xy_to_lonlat_args_t
{
    double longitude;
    double latitude;
} xy_to_lonlat_args_t;

esp_err_t xy_to_lonlat(
    xy_to_lonlat_args_t* return_struct,
    uint32_t             x,
    uint32_t             y,
    uint32_t             width,
    uint32_t             height
);

///////////////////////////////////////////////////////////
#endif // NEOPIXEL_MATRIX_H
///////////////////////////////////////////////////////////
