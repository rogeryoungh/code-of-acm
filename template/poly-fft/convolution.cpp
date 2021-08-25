#ifndef ACM_POLY_CONVOLUTION_H
#define ACM_POLY_CONVOLUTION_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "fft.cpp"
#endif

namespace poly {

void convolution(poly_t &f, poly_t &g, int deg = lim) {

    poly::fft(f, deg);
    if (f != g)
        poly::fft(g, deg);

    for (int i = 0; i <= lim; i++)
        f[i] = f[i] * g[i];

    poly::ifft(f, deg);
}

} // namespace poly

#endif