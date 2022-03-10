#ifndef ACM_NTT_PRE_W_H
#define ACM_NTT_PRE_W_H

#include "template/math/qpow.hpp"
#include "template/basic/mint/0.hpp"

vector<m32> w, Inv, fac, ifac;

inline int get_lim(int n, int s = 1) {
    int m = 1;
    while (m < n)
        m <<= s;
    return m;
}

void pre_w(int n, int w0 = 3) {
    static int lim = (w = {1, 1}, 2);
    n = get_lim(n);
    if (n <= lim)
        return;
    w.resize(n);
    for (int l = lim; l < n; l *= 2) {
        m32 p = m32(w0).pow((P - 1) / l / 2);
        for (int i = 0; i < l; i += 2) {
            w[(l + i)] = w[(l + i) / 2];
            w[l + i + 1] = w[l + i] * p;
        }
    }
    lim = n;
}

#endif
