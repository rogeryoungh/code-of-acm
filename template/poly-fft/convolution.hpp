#ifndef ACM_POLY_CONVOLUTION_H
#define ACM_POLY_CONVOLUTION_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "fft.hpp"
#endif

namespace poly {

void convolution(poly_t f[], poly_t g[], poly_t ans[], int deg = lim) {

    poly::fft(f, deg);
    if (f != g)
        poly::fft(g, deg);

    for (int i = 0; i <= lim; i++)
        ans[i] = f[i] * g[i];

    poly::ifft(f, deg);
}

} // namespace poly

#endif