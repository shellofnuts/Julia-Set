#ifndef JULIA_H
#define JULIA_H

#include <complex>
#include <vector>
#include "window.h"

using Complex = std::complex<double>;

Complex C(-0.8, 0.156);
int MAX_ITER = 2000;

void julia_set();
Complex polynomial(Complex z);
int get_iterations(Complex z);
void calc_fractal(Window<int> &scrn, Window<double> &frac, std::vector<int> &colours);


#endif JULIA_H