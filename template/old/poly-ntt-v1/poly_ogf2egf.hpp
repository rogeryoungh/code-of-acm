#ifndef ACM_POLY_OGF2EGF_H
#define ACM_POLY_OGF2EGF_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"
#endif

namespace poly {

void OGF2EGF(int f[], int ans[], int deg = lim) {
    ll fact = 1;
    ans[0] = f[0];
    for (ll i = 1; i <= deg; i++) {
        fact = fact * i % mod;
        ans[i] = f[i] * inv(fact) % mod;
    }
}

} // namespace poly

#endif
