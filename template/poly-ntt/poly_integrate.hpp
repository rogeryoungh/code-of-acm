#ifndef ACM_POLY_INTEGRATE_H
#define ACM_POLY_INTEGRATE_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#endif

namespace poly {

void integrate(const poly_t h[], poly_t ans[], const int deg = lim) {
    for (int i = deg - 1; i; --i)
        ans[i] = h[i - 1] * inv(i) % mod;
    ans[0] = 0; /* C */
}

} // namespace poly

#endif