#ifndef ACM_POLY_LN_H
#define ACM_POLY_LN_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "init_rev.hpp"
#include "ntt.hpp"
#include "poly_inv.hpp"
#include "poly_derivative.hpp"
#include "poly_integrate.hpp"
#endif

namespace poly {

void poly_ln(const int *h, int *ans, const int deg = lim) {
    static Poly ln_t;
    const int deg2 = deg >> 1;

    derivative(h, ln_t, deg2);
    std::fill(ln_t + deg2, ln_t + deg, 0);
    poly_inv(h, ans, deg);

    ntt(ln_t, deg);
    ntt(ans, deg);
    for (int i = 0; i < deg; ++i)
        ln_t[i] = mul(ln_t[i], ans[i]);
    intt(ln_t, deg);

    integrate(ln_t, ans, deg2);
}

} // namespace poly

#endif
