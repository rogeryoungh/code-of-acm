#ifndef ACM_POLY_INIT_INV_H
#define ACM_POLY_INIT_INV_H

#ifndef RYLOCAL
#include "../__base.hpp"
#include "../poly.hpp"
#endif

void pre_inv(int n) {
    static int LIM = (Inv = {1, 1}, 2);
    if (n <= LIM)
        return;
    Inv.resize(n);
    for (int i = LIM; i < n; i++) {
        Inv[i] = Inv[P % i] * (P - P / i);
    }
    LIM = n;
}

Poly getInv(Poly f) {
    int sz = f.deg() + 1;
    Poly s(sz);
    s[0] = 1;
    for (int i = 0; i < f.deg(); i++)
        s[i + 1] = s[i] * f[i];
    Poly iv(f.deg());
    m32 mul = s[f.deg()].inv();
    for (int i = f.deg(); i >= 1; i--) {
        iv[i - 1] = mul * s[i - 1];
        mul = mul * f[i - 1];
    }
    return iv;
}

#endif