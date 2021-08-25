#ifndef ACM_POLY_CONVOLUTION_H
#define ACM_POLY_CONVOLUTION_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "ntt.cpp"
#endif

namespace poly {

void convolution(poly_t &f, poly_t &g) {
    poly::ntt(f);
    if (f != g)
        poly::ntt(g);
    for (int i = 0; i <= lim; i++)
        f[i] = f[i] * g[i];
    poly::intt(f);
}

} // namespace poly

#endif