#ifndef ACM_POLY_CONVOLUTION_H
#define ACM_POLY_CONVOLUTION_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "fft.hpp"
#endif

namespace poly {

void convolution(img *f, img *g, img *ans, int deg = lim) {

    poly::fft(f, deg);

    if (f != g)
        poly::fft(g, deg);

    for (int i = 0; i < lim; i++)
        ans[i] = f[i] * g[i];

    poly::ifft(ans, deg);
}

void convolution(img *f, img *g, int deg = lim) {
    convolution(f, g, f, deg);
}

} // namespace poly

#endif