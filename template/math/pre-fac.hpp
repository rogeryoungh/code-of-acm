#ifndef ACM_MATH_PRE_FAC_H
#define ACM_MATH_PRE_FAC_H

#include "template/math/qpow.hpp"

vi pre_fac(int n) {
    vi fac(n);
    fac[0] = 1;
    for (int i = 1; i < n; i++) {
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    return fac;
}

vi pre_ifac(const vi& fac, int n) {
    vi ifac(n)
    ifac[0] = fac[0] = 1;
    for (ll i = 1; i < lim; i++) {
        fac[i] = mul(fac[i - 1], i);
    }
    ifac[lim - 1] = inv(fac[lim - 1]);
    for (ll i = lim - 2; i > 0; i--) {
        ifac[i] = mul(ifac[i + 1], i + 1);
    }
}

#endif
