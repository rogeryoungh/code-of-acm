#ifndef ACM_NTT_PRE_FAC_H
#define ACM_NTT_PRE_FAC_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#include "../basic/mint.hpp"
#endif

poly_t pre_fac(int lim) {
    poly_t fac(lim);
    fac[0] = 1;
    for (int i = 1; i < lim; i++) {
        fac[i] = fac[i - 1] * i;
    }
    return fac;
}

poly_t pre_ifac(const poly_t &fac) {
    int lim = fac.size();
    poly_t ifac(lim);
    ifac[lim - 1] = fac[lim - 1].inv();
    for (int i = lim - 2; i > 0; i--) {
        ifac[i] = ifac[i + 1] * (i + 1);
    }
    ifac[0] = 0;
    return ifac;
}

#endif
