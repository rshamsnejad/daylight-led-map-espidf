def xy_to_index(
        x:              int,
        y:              int,
        width:          int  = 32,
        height:         int  = 16,
        zigzag:         bool = True,
        row_major:      bool = True,
        flip_x:         bool = False,
        flip_y:         bool = False,
        square_split_x: bool = False
    ) -> int:
    """
    Translates (X, Y) coordinates into Neopixel matrix index.

    Args:
        x              (int):  X coordinate (0 to width-1).
        y              (int):  Y coordinate (0 to height-1).
        width          (int):  Matrix width. Default is 32.
        height         (int):  Matrix height. Default is 16.
        zigzag         (bool): True if wired in zigzag, False if wired in progressive. Defaults to True.
        row_major      (bool): True if wired row by row, False if wired column by column. Defaults to True.
        flip_x         (bool): True if X-axis mirroring is needed, False otherwise. Defaults to False.
        flip_y         (bool): True if Y-axis mirroring is needed, False otherwise. Defaults to False.
        square_split_x (bool): True if the matrix is made of 2 parts along the X-axis, False otherwise. Defaults to False.

    Returns:
        int: The NeoPixel index (0-based).
    """
    
    if x < 0 or x >= width or y < 0 or y >= height:
        raise ValueError("x or y is out of bounds")
    if square_split_x and width / 2 != height:
        raise ValueError("Invalid width for a square split")

    if flip_x:
        x = width - 1 - x
    if flip_y:
        y = height - 1 - y
    
    base = 0
    offset = 0
    compute_width = width

    # print(f"(x, y) = ({x}, {y})")

    if square_split_x:

        compute_width = int(width / 2)

        if x >= width / 2:
            offset = int( (width * height) / 2 )
            x -= int( (width / 2) )
    
    # print(f"offset = {offset}")
    # print(f"(x, y) = ({x}, {y})")
    
    if row_major:
        if zigzag:
            if y % 2 == 0:
                # Even rows go left to right
                base = y * compute_width + x
            else:
                # Odd rows go right to left
                base = y * compute_width + (compute_width - 1 - x)
        else:
            base = y * compute_width + x
    else:
        if zigzag:
            if x % 2 == 0:
                base = x * height + y
            else:
                base = x * height + (height - 1 - y)
        else:
            base = x * height + y

    return base + offset

def xy_to_lonlat(x, y, width=32, height=16):
    """
    Converts x, y coordinates in an arbitrary range (0 to x_max, 0 to y_max)
    to longitude and latitude using the Plate Carrée projection.

    Parameters:
        x (float or array-like): x-coordinate(s) in the range [0, x_max]
        y (float or array-like): y-coordinate(s) in the range [0, y_max]
        x_max (float): maximum value of x (corresponds to longitude 180°)
        y_max (float): maximum value of y (corresponds to latitude 90°)

    Returns:
        tuple: (longitude, latitude)
    """
    # Normalize x and y to [0, 1]
    x_norm = x / width
    y_norm = y / height

    # Map to longitude [-180, 180] and latitude [-90, 90]
    lon = x_norm * 360.0 - 180.0
    lat = y_norm * 180.0 - 90.0

    return lon, lat