#include <iostream>
#include <complex>
#include <functional>

#include "window.h"
#include "julia.h"
#include "plot_image.h"

using Complex = std::complex<double>;

Complex polynomial(Complex z) { return z*z + C; }

Complex scale(Window<int> &scrn, Window<double> &frac, Complex z)
{
    Complex rescaled;
    rescaled.real((z.real() - scrn.y_min()) * (frac.height() / scrn.height()) + frac.y_min());
    rescaled.imag((z.imag() - scrn.x_min()) * (frac.width() / scrn.width()) + frac.x_min());
    return rescaled;
}

int get_iterations(Complex z)
{
    int iter = 0;
    while (abs(z) < 2.0 && iter <= MAX_ITER)
    {
        z = polynomial(z);
        ++iter;
    }
    
    return iter;
}

void calc_fractal(Window<int> &scrn, Window<double> &frac, std::vector<int> &colours)
{
    int k = 0, progress = 0;
    for (int j = scrn.y_min(); j < scrn.y_max(); ++j)
    {
        for (int i = scrn.x_min(); i < scrn.x_max(); ++i)
        {
            Complex z((double) i, (double) j);
            z = scale(scrn, frac, z);
            colours[k] = get_iterations(z);
            ++k;
        }
        if (progress < (int)((j - scrn.y_min())/(scrn.height())*100.0))
        {
            progress = (int)((j - scrn.y_min())/(scrn.height())*100.0);
            std::cout << progress << "\n";
        }
    }
}

void julia_set()
{
    Window<int> screen(0, 1200, 0, 1200);
    Window<double> fractal(-1.5, 1.5, -1.5, 1.5);

    const char *filename = "Julia_Set.png";
    std::vector<int> colours(screen.size());

    calc_fractal(screen, fractal, colours);

    plot(screen, colours, MAX_ITER, filename);
}

int main(){
    julia_set();
}