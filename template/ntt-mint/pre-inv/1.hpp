#ifndef ACM_NTT_PRE_INV_H
#define ACM_NTT_PRE_INV_H

#include "template/basic/mint/0.hpp"

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

#endif
