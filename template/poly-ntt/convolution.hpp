#ifndef ACM_POLY_CONVOLUTION_H
#define ACM_POLY_CONVOLUTION_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "ntt.hpp"
#endif

namespace poly {

void convolution(poly_t f[], poly_t g[], poly_t ans[], int deg = lim) {
    poly::ntt(f);
    if (f != g)
        poly::ntt(g, deg);
    for (int i = 0; i <= lim; i++)
        ans[i] = f[i] * g[i];
    poly::intt(ans, deg);
}

} // namespace poly

#endif