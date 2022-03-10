#ifndef ACM_POLY_NTT_H
#define ACM_POLY_NTT_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/mo.hpp"
#endif

namespace poly {

void ntt(int *f, int deg = lim, int type = 1) {
    for (int i = 0; i < deg; ++i) {
        if (i < rev[i]) {
            std::swap(f[i], f[rev[i]]);
        }
    }
    for (int h = 2; h <= deg; h <<= 1) {
        int tg = type == 1 ? 3 : g_inv;
        int gn = qpow(tg, (mod - 1) / h, mod);
        for (int j = 0; j < deg; j += h) {
            int g = 1;
            for (int k = j; k < j + h / 2; k++) {
                int f1 = f[k], f2 = mul(g, f[k + h / 2]);
                f[k] = add(f1, f2);
                f[k + h / 2] = sub(f1, f2);
                g = mul(g, gn);
            }
        }
    }
    int deg_inv = mod - (mod - 1) / deg;
    if (type != 1)
        for (int i = 0; i < deg; i++)
            f[i] = mul(f[i], deg_inv);
}

void intt(int *f, int deg = lim) {
    ntt(f, deg, -1);
}

} // namespace poly

#endif