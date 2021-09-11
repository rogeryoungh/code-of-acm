#ifndef ACM_POLY_EGF2OGF_H
#define ACM_POLY_EGF2OGF_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.cpp"
#include "../basic/inv.cpp"
#endif

namespace poly {

void EGF2OGF(poly_t f[], poly_t ans[], int deg = lim) {
    ll fact = 1;
    ans[0] = f[0];
    for (ll i = 1; i <= deg; i++) {
        fact = fact * i % mod;
        ans[i] = f[i] * fact % mod;
    }
}

} // namespace poly

#endif
