#include "color.h"

// Maps a number to a color using the HSV color space and converts it to an RGB pixel
png::rgb_pixel color_map(float n, float max) {
    // Calculate the value for hue based on the input n
    float h = 360.0 * n / max;

    // Saturation and value are fixed to give bright colors
    float s = 0.9;
    float v = 0.8;

    // Convert HSV to RGB using the algorithm
    int hi = floor(h/60.0);
    float f = (h / 60.0) - hi;
    float p = v * (1 - s);
    float q = v * (1 - s * f);
    float t = v * (1 - s * (1 - f));
    
    float r, g, b;
    switch (hi) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }

    // Scale the RGB values to the range [0, 255]
    return png::rgb_pixel(static_cast<unsigned char>(r * 255),
                          static_cast<unsigned char>(g * 255),
                          static_cast<unsigned char>(b * 255));
}

