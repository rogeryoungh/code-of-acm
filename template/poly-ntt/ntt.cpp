#ifndef ACM_POLY_NTT_H
#define ACM_POLY_NTT_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/mo.cpp"
#include "../basic/qpow.cpp"
#include "../basic/inv.cpp"
#endif

namespace poly {

void ntt(poly_t &f, int deg = lim, int type = 1) {
    for (int i = 0; i < deg; ++i) {
        if (i < rev[i]) {
            std::swap(f[i], f[rev[i]]);
        }
    };
    for (int h = 2; h <= deg; h <<= 1) {
        ll tg = type == 1 ? 3 : g_inv;
        ll gn = qpow(tg, (mod - 1) / h, mod);
        for (int j = 0; j < deg; j += h) {
            ll g = 1;
            for (int k = j; k < j + h / 2; k++) {
                ll f1 = f[k], f2 = g * f[k + h / 2] % mod;
                f[k] = mo(f1 + f2);
                f[k + h / 2] = mo(f1 - f2);
                g = g * gn % mod;
            }
        }
    }
    if (type == 1)
        return;
    ll lim_inv = inv(deg, mod);
    for (int i = 0; i < deg; i++)
        f[i] = f[i] * lim_inv % mod;
}

void intt(poly_t &f, int deg = lim) {
    ntt(f, deg, -1);
}

} // namespace poly

#endif