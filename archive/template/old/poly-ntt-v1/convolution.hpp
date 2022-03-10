#ifndef ACM_POLY_CONVOLUTION_H
#define ACM_POLY_CONVOLUTION_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "ntt.hpp"
#endif

namespace poly {

void convolution(int *f, int *g, int *ans, int deg = lim) {
    ntt(f);
    if (f != g)
        ntt(g, deg);
    for (int i = 0; i < deg; i++)
        ans[i] = mul(f[i], g[i]);
    intt(ans, deg);
}

void convolution(int *f, int *g, int deg = lim) {
    convolution(f, g, f, deg);
}

} // namespace poly

#endif