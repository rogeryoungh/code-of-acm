#ifndef ACM_NTT_PRE_W_H
#define ACM_NTT_PRE_W_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/qpow.hpp"
#include "../basic/mint.hpp"
#endif

int get_lim(int sum) {
    int lim = 1, k = 0;
    while (lim < sum)
        lim <<= 1, k++;
    return lim;
}

void pre_w(int n) {
    static int LIM = 1;
    int lim = get_lim(n), g = 3;
    if (lim <= LIM)
        return;
    w.resize(lim);
    for (int l = LIM; l < lim; l *= 2) {
        int p = qpow(g, (P - 1) / l / 2, P);
        w[l] = 1; // w[j + l] = w_{2l} ^ j
        for (int i = 1; i < l; i++)
            w[l + i] = w[l + i - 1] * p;
    }
    LIM = lim;
}

#endif