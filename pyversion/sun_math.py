import math
import time

def sun_position(utc_timestamp):
    """
    Calculates the solar declination and subsolar longitude for a given UTC timestamp.
    
    Returns:
        delta (float): Solar declination in radians
        subsolar_lon (float): Subsolar point longitude in degrees
    """
    tm = time.gmtime(utc_timestamp)
    # N = tm.tm_yday
    N = tm[7]
    # hour = tm.tm_hour + tm.tm_min / 60 + tm.tm_sec / 3600
    hour = tm[3] + tm[4] / 60 + tm[5] / 3600

    # Fractional year in radians
    gamma = 2 * math.pi / 365 * (N - 1 + hour / 24)

    # Equation of Time (in minutes)
    EoT = 229.18 * (
        0.000075
        + 0.001868 * math.cos(gamma)
        - 0.032077 * math.sin(gamma)
        - 0.014615 * math.cos(2 * gamma)
        - 0.040849 * math.sin(2 * gamma)
    )

    # Solar declination (in radians)
    delta = (
        0.006918
        - 0.399912 * math.cos(gamma)
        + 0.070257 * math.sin(gamma)
        - 0.006758 * math.cos(2 * gamma)
        + 0.000907 * math.sin(2 * gamma)
        - 0.002697 * math.cos(3 * gamma)
        + 0.00148 * math.sin(3 * gamma)
    )

    # Subsolar longitude (in degrees, range [-180, 180])
    subsolar_lon = (180 - (hour * 15 + EoT * 0.25)) % 360 - 180

    return delta, subsolar_lon

def is_daytime(lon, lat, delta, lambda_s):
    """
    Determine if the (lat, lon) point is in daylight.
    """
    H = math.radians(lon - lambda_s)
    cos_chi = math.sin(-lat) * math.sin(delta) + math.cos(-lat) * math.cos(delta) * math.cos(H)
    return cos_chi <= 0