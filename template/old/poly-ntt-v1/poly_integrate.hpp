#ifndef ACM_POLY_INTEGRATE_H
#define ACM_POLY_INTEGRATE_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#endif

namespace poly {

void integrate(const int *h, int *ans, const int deg = lim) {
    for (int i = deg - 1; i; --i)
        ans[i] = mul(h[i - 1], Inv[i]);
    ans[0] = 0; /* C */
}

void integrate(int *h, const int deg = lim) {
    integrate(h, h, deg);
}

} // namespace poly

#endif