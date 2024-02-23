#include "complex_numbers.h" // Include for complex number operations
#include <png++/png.hpp>     // Include for handling PNG images
#include "color.h"           // Include for color mapping
#include <cmath>
#include <iostream>
#include <string>
#include <omp.h>             // Include for OpenMP parallelization

using namespace std;
using image = png::image<png::rgb_pixel>;

// Function to determine the number of iterations before divergence
int steps(const complex_numbers &c, double limit, int max = 100){
    complex_numbers z = 0;
    for (int i = 0; i < max; ++i){
        z = z*z + c;  // Mandelbrot iteration
        if (z.abs() > limit){
            return i;
        }
    }
    return max;
}

// Halton sequence generator for quasi-random numbers
double halton(int index, int base) {
    double result = 0.0;
    double f = 1.0 / double(base);
    int i = index;
    while (i > 0) {
        result += f * (i % base);
        i = i / base;
        f = f / double(base);
    }
    return result;
}

int main(int argc, char** argv){
    if (argc != 4 && argc != 8) {
        cerr << "Incorrect number of arguments supplied." << endl;
        cerr << "Usage:" << endl;
        cerr << argv[0] << " width height output-name [xmin xmax ymin ymax]" << endl;
        return -1;
    }
    
    int width = stoi(argv[1]);
    int height = stoi(argv[2]);
    string filename = argv[3];
    image result(width, height);

    // Set default Mandelbrot viewport
    double xmin = -2, xmax = 2;
    double ymin = -2, ymax = 2;
    if (argc == 8) {
        // Use custom viewport if provided
        xmin = atof(argv[4]);
        xmax = atof(argv[5]);
        ymin = atof(argv[6]);
        ymax = atof(argv[7]);
    }

    if (width <= 0 || height <= 0) {
        cerr << "Invalid image dimensions: " << width << " x " << height << endl;
        return -2;
    }

    int max_it = 3000;  // Maximum number of iterations
    int max_col = 437;  // Maximum color index

    // Parallelize the loop using OpenMP
#pragma omp parallel for
    for (int y = 0; y < height ;++y){
        for (int x = 0; x < width; ++x){
            
            int n = 0;
            // Sample 8 points for anti-aliasing using Halton sequence
            for (int i = 0; i < 8; ++i) {
                complex_numbers c((xmax-xmin)*(x+halton(i,2)-0.5)/width, (ymax-ymin)*(y+halton(i,3)-0.5)/height);
                c += complex_numbers(xmin, ymin);
                n += steps(c, 2, max_it);
            }
            n /= 8.0;
            // Set pixel color based on the number of iterations
            if (n != max_it) {
                result.set_pixel(x, y, color_map(n % max_col, max_col));
            }
            
        }
    }
    result.write(filename);
}
