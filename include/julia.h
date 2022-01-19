#ifndef JULIA_H
#define JULIA_H

#include <complex>
#include <vector>
#include "window.h"

using Complex = std::complex<double>;
class JuliaSet
{
private:
    Complex _C{0.285, 0.01}; // Initialise C with a default value
    const int MAX_ITER = 800;
    Window<int> screen{0, 2000, 0, 2000};
    Window<double> fractal{-1.5, 1.5, -1.5, 1.5};
    std::vector<int> colours = std::vector<int>(screen.size());
    const char *_filename;

    Complex scale(Complex z);
    Complex polynomial(Complex z);
    int get_iterations(Complex z);

public:
    JuliaSet(const char *filename) : _filename(filename){};
    void calc_fractal();

    void setHeight(double height);
    void setWidth(double width);
    void plotFractal();

    // Setters & Getters
    void filename(const char *filename) { _filename = filename; };
    const char *filename() { return _filename; };
    void setC(Complex C) { _C = C; };
    Complex getC() { return _C; };
};

#endif JULIA_H