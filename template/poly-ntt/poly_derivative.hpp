#ifndef ACM_POLY_DERIVATIVE_H
#define ACM_POLY_DERIVATIVE_H

#ifndef RYLOCAL
#include "__base.hpp"

#endif

namespace poly {

void derivative(const poly_t f[], poly_t ans[], const int deg = lim) {
    for (int i = 1; i < deg; ++i)
        ans[i - 1] = f[i] * i % mod;
    ans[deg - 1] = 0;
}

} // namespace poly

#endif
