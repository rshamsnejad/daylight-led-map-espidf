#include "esp_err.h"
#include "global.h"
#include "neopixel_matrix.h"

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
)
{
    if(x >= width || y >= height)
    {
        return ESP_ERR_INVALID_ARG;
    }

    if(flip_x)
    {
        x = width - 1 - x;
    }
    if(flip_y)
    {
        y = height - 1 - y;
    }

    uint32_t base = 0;
    uint32_t offset = 0;
    uint32_t compute_width = width;

    if(square_split_x)
    {
        compute_width = (uint32_t)(width / 2.0);

        if(x >= (width / 2))
        {
            offset = (uint32_t)((width * height) / 2.0);
            x -= (uint32_t)(width / 2.0);
        }
    }

    if(row_major)
    {
        if(zigzag)
        {
            if(y % 2 == 0)
            {
                // Even rows go left to right
                base = y * compute_width + x;
            }
            else
            {
                // Odd rows go right to left
                base = y * compute_width + (compute_width - 1 - x);
            }
        }
        else
        {
            base = y * compute_width + x;
        }
    }
    else
    {
        if(zigzag)
        {
            if(x % 2 == 0)
            {
                base = x * height + y;
            }
            else
            {
                base = x * height + (height - 1 - y);
            }
        }
        else
        {
            base = x * height + y;
        }
    }

    return_struct->index = base + offset;

    return ESP_OK;
}

esp_err_t xy_to_lonlat(
    xy_to_lonlat_args_t* return_struct,
    uint32_t             x,
    uint32_t             y,
    uint32_t             width,
    uint32_t             height
)
{
    double x_norm = x / width;
    double y_norm = y / height;
    
    double lon = x_norm * 360.0 - 180.0;
    double lat = y_norm * 180.0 - 90.0;

    return_struct->longitude = lon;
    return_struct->latitude = lat;

    return ESP_OK;
}