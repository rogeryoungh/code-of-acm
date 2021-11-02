#ifndef ACM_POLY_NTT_H
#define ACM_POLY_NTT_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/mo.hpp"
#endif

void ntt(poly_t &f, int deg) {
    for (int l = deg >> 1; l; l >>= 1)
        for (int i = 0; i < deg; i += (l << 1))
            for (int j = 0; j < l; j++) {
                Mint x = f[i + j] + f[i + j + l];
                f[i + j + l] = w[j + l] * (f[i + j] - f[i + j + l]);
                f[i + j] = x;
            }
}

void intt(poly_t &f, int deg) {
    for (int l = 1; l < deg; l <<= 1)
        for (int i = 0; i < deg; i += (l << 1))
            for (int j = 0; j < l; j++) {
                Mint x = f[i + j], y = f[i + j + l] * w[j + l];
                f[i + j] = x + y, f[i + j + l] = x - y;
            }
    const Mint deg_inv = mod - (mod - 1) / deg;
    for (int i = 0; i < deg; i++)
        f[i] *= deg_inv;
    std::reverse(f.begin() + 1, f.begin() + deg);
}

void ntt(poly_t &f) {
    ntt(f, f.size());
}

void intt(poly_t &f) {
    intt(f, f.size());
}

#endif