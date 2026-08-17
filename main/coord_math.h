///////////////////////////////////////////////////////////
#ifndef NEOPIXEL_MATRIX_H
#define NEOPIXEL_MATRIX_H
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

/// @brief Return struct for xy_to_index()
/// @param index The computed neopixel index
typedef struct xy_to_index_args_t
{
    uint32_t index;
} xy_to_index_args_t;

/// @brief Converts (x,y) coordinates into neopixel matrix index
/// @param return_struct 
/// @param x x coordinate (0, width-1)
/// @param y y coordinate (0, height-1)
/// @param width Width of the matrix
/// @param height Height of the matrix
/// @param zigzag Set to true if the panel is wired in zigzag
/// @param row_major Set to true if the wiring is done by rows, false if done by columns
/// @param flip_x Set to true to mirror along x
/// @param flip_y Set to true to mirror along y
/// @param square_split_x Set to true if the matrix is made of two squares wired in series
/// @return ESP error code
esp_err_t xy_to_index
(
    xy_to_index_args_t* return_struct,
    uint32_t            x,
    uint32_t            y,
    uint32_t            width,
    uint32_t            height,
    bool                zigzag,
    bool                row_major,
    bool                flip_x,
    bool                flip_y,
    bool                square_split_x
);

/// @brief Return struct for xy_to_lonlat()
/// @param longitude Computed longitude [-180°, 180°]
/// @param latitude Computed latitude [-90°, 90°]
typedef struct xy_to_lonlat_args_t
{
    double longitude;
    double latitude;
} xy_to_lonlat_args_t;

/// @brief Converts (x,y) coordinates to Earth coordinates using the PlateCarree projection
/// @param return_struct 
/// @param x x coordinate (0, width-1)
/// @param y y coordinate (0, height-1)
/// @param width Width of the matrix
/// @param height Height of the matrix
/// @return ESP error code
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
