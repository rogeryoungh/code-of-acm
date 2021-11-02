#ifndef ACM_NTT_EGF_H
#define ACM_NTT_EGF_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mint.hpp"
#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"
#endif

poly_t ntt_egf2ogf(const poly_t &f, int deg) {
    poly_t ans(deg);
    ans[0] = f[0];
    for (int i = 1; i < deg; i++) {
        ans[i] = f[i] * fac[i];
    }
    return ans;
}

poly_t ntt_ogf2egf(const poly_t &f, int deg) {
    poly_t ans(deg);
    ans[0] = f[0];
    for (int i = 1; i < deg; i++) {
        ans[i] = f[i] * ifac[i];
    }
    return ans;
}

#endif
