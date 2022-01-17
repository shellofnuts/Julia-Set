#include "window.h"
#include "plot_image.h"
#include "FreeImage.h"
#include <tuple>
#include <vector>
#include <math.h>

std::tuple<int, int, int> get_RGBDiscreteColours(int colour_index, int max_iters)
{
    int N = 256;            // RGB has 256 values on each channel
    int N3 = N * N * N;     // Our RGB space as a 3D matrix with 256 points on each axis
    
    // Imagine our colour value corresponds to a "row-order" style coordinate
    // in our RGB 3D matrix

    int b = colour_index / (N * N);
    int less_b = colour_index - (b * N * N);
    int r = less_b / N;
    int g = less_b - (r * N);

    return std::tuple<int, int, int>(r, g, b);
}

std::tuple<int, int, int> get_RGBContinuousColours(int colour_index, int max_iters)
{
    double tmp = (double) colour_index / (double) max_iters;

    int r = (int) 9 * (1 - tmp) * pow(tmp, 3) * 255;
    int g = (int) 15 * pow((1-tmp), 2) * pow(tmp, 2) * 255;
    int b = (int) 8.5 * pow((1 - tmp), 3) * tmp * 255;

    return std::tuple<int, int, int>(r, g, b);
}

void plot(Window<int> &screen, std::vector<int> colours, int max_iter, const char *filename)
{
    unsigned int width = screen.width(), height = screen.height();
    FIBITMAP *bitmap = FreeImage_Allocate(width, height, 32);

    std::tuple<int, int, int> rgb;
    int k = 0;

    for (int j = screen.y_min(); j < screen.y_max(); ++j)
    {
        for (int i = screen.x_min(); i < screen.x_max(); ++i)
        {
            rgb = get_RGBContinuousColours(colours[k], max_iter);

            RGBQUAD bitcolours;
            bitcolours.rgbRed = std::get<0>(rgb);
            bitcolours.rgbGreen = std::get<1>(rgb);
            bitcolours.rgbBlue = std::get<2>(rgb);
            bitcolours.rgbReserved = 255;   // Set alpha to solid colour.

            FreeImage_SetPixelColor(bitmap, i, j, &bitcolours);
            ++k;
        }
    }

    FreeImage_Save(FIF_PNG, bitmap, filename, PNG_DEFAULT);
    FreeImage_Unload(bitmap);
}