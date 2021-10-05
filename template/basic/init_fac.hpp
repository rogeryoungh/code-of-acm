#ifndef ACM_BASIC_INIT_FAC_H
#define ACM_BASIC_INIT_FAC_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "mo.hpp"
#endif

void init_fac(ll *fac, int lim) {
    fac[0] = 1;

    for (ll i = 1; i < lim; i++) {
        fac[i] = mul(fac[i - 1], i);
    }
}

void init_ifac(ll *fac, ll *ifac, int lim, const ll *Inv) {
    ifac[0] = fac[0] = 1;
    for (ll i = 1; i < lim; i++) {
        fac[i] = mul(fac[i - 1], i);
        ifac[i] = mul(ifac[i], Inv[i]);
    }
}

#endif