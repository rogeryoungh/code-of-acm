#ifndef ACM_NTT_PRE_FAC_H
#define ACM_NTT_PRE_FAC_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#include "../basic/mint.hpp"
#endif

Poly pre_fac(int lim) {
    Poly fac(lim);
    fac[0] = 1;
    for (int i = 1; i < lim; i++) {
        fac[i] = fac[i - 1] * i;
    }
    return fac;
}

Poly pre_ifac(const Poly &fac) {
    int lim = fac.size();
    Poly ifac(lim);
    ifac[lim - 1] = inv(fac[lim - 1].v);
    for (int i = lim - 2; i > 0; i--) {
        ifac[i] = ifac[i + 1] * (i + 1);
    }
    ifac[0] = 0;
    return ifac;
}

#endif
