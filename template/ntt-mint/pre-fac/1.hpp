#ifndef ACM_NTT_PRE_FAC_H
#define ACM_NTT_PRE_FAC_H

void pre_fac(int lim) {
    fac.resize(lim + 1);
    fac[0] = 1;
    for (int i = 1; i <= lim; i++) {
        fac[i] = fac[i - 1] * i;
    }
}

void pre_ifac(int lim) {
    ifac.resize(lim + 1);
    ifac[lim] = fac[lim].inv();
    for (int i = lim - 1; i >= 0; i--) {
        ifac[i] = ifac[i + 1] * (i + 1);
    }
}

#endif
