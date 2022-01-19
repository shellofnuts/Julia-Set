#include <iostream>
#include <complex>
#include <functional>

#include "window.h"
#include "julia.h"
#include "plot_image.h"

using Complex = std::complex<double>;

Complex JuliaSet::polynomial(Complex z) { return z*z + _C; }

Complex JuliaSet::scale(Complex z)
{
    Complex rescaled;
    rescaled.real((z.real() - screen.y_min()) * (fractal.height() / screen.height()) + fractal.y_min());
    rescaled.imag((z.imag() - screen.x_min()) * (fractal.width() / screen.width()) + fractal.x_min());
    return rescaled;
}

int JuliaSet::get_iterations(Complex z)
{
    int iter = 0;
    while (abs(z) < 1.0 && iter <= MAX_ITER)
    {
        z = this->polynomial(z);
        ++iter;
    }
    
    return iter;
}

void JuliaSet::calc_fractal()
{
    int k = 0, progress = 0;
    for (int j = screen.y_min(); j < screen.y_max(); ++j)
    {
        for (int i = screen.x_min(); i < screen.x_max(); ++i)
        {
            Complex z((double) i, (double) j);
            z = this->scale(z);
            colours[k] = this->get_iterations(z);
            ++k;
        }
        if (progress < (int)((j - screen.y_min())/(screen.height())*100))
        {
            progress = (int)((j - screen.y_min())/(screen.height())*100);
            std::cout << progress << std::endl;
        }
    }
}

void JuliaSet::plotFractal()
{
    plot(screen, colours, MAX_ITER, _filename);
}

void JuliaSet::setHeight(double height)
{
    fractal = Window<double>(fractal.x_min(), fractal.x_max(), -1 * height / 2, height / 2);
}

void JuliaSet::setWidth(double width)
{
    fractal = Window<double>(-1 * width / 2, width / 2, fractal.y_min(), fractal.y_max());
}

int main(){
    JuliaSet image1("Julia_Set_1.png");
    image1.calc_fractal();
    image1.plotFractal();
}