#ifndef ACM_POLY_INIT_INV_H
#define ACM_POLY_INIT_INV_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mint.hpp"
#endif

void pre_inv(int n) {
    static int LIM = 2;
    if (n <= LIM)
        return;
    Inv.resize(n);
    for (int i = LIM; i < n; i++) {
        Inv[i] = Inv[P % i] * (P - P / i);
    }
    LIM = n;
}

#endif