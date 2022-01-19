#ifndef PLOT_IMAGE_H
#define PLOT_IMAGE_H

#include "window.h"
#include <vector>

void plot(Window<int> &screen, std::vector<int> &colours, int max_iter, const char *filename);

#endif PLOT_IMAGE_H