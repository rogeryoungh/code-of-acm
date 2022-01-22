#ifndef ACM_POLY_NTT_H
#define ACM_POLY_NTT_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/mint.hpp"

#include "pre_w.hpp"
#endif

void ntt(Poly::iterator f, int deg) {
    pre_w(deg);
    for (int l = deg >> 1; l; l >>= 1)
        for (auto fi = f; fi - f < deg; fi += (l << 1))
            for (int j = 0; j < l; j++) {
                Mint x = fi[j] + fi[j + l];
                fi[j + l] = w[j + l] * (fi[j] - fi[j + l]);
                fi[j] = x;
            }
}

void intt(Poly::iterator f, int deg) {
    for (int l = 1; l < deg; l <<= 1)
        for (auto fi = f; fi - f < deg; fi += (l << 1))
            for (int j = 0; j < l; j++) {
                Mint x = fi[j], y = fi[j + l] * w[j + l];
                fi[j] = x + y, fi[j + l] = x - y;
            }
    const Mint deg_inv = P - (P - 1) / deg;
    for (int i = 0; i < deg; i++)
        f[i] *= deg_inv;
    std::reverse(f + 1, f + deg);
}

void ntt(Poly &f) {
    ntt(f.begin(), f.size());
}

void intt(Poly &f) {
    intt(f.begin(), f.size());
}

#endif