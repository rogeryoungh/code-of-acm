#ifndef ACM_NTT_EGF_H
#define ACM_NTT_EGF_H

#ifndef RYLOCAL
#include "../__base.hpp"
#include "../poly.hpp"
#endif

Poly ntt_egf2ogf(const Poly &f, int deg) {
    Poly ans(deg);
    ans[0] = f[0];
    for (int i = 1; i < deg; i++) {
        ans[i] = f[i] * fac[i];
    }
    return ans;
}

Poly ntt_ogf2egf(const Poly &f, int deg) {
    Poly ans(deg);
    ans[0] = f[0];
    for (int i = 1; i < deg; i++) {
        ans[i] = f[i] * ifac[i];
    }
    return ans;
}

#endif
