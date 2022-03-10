#ifndef ACM_POLY_MUL_H
#define ACM_POLY_MUL_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#include "ntt_inv.hpp"
#include "ntt_d.hpp"
#include "ntt_int.hpp"
#endif

Poly &operator*=(Poly &f, Poly &g) {
    int lim = f.size();
    ntt(f);
    if (f.data() != g.data())
        ntt(g);
    for (int i = 0; i < lim; i++)
        f[i] *= g[i];
    intt(f);
    return f;
}

Poly &operator+=(Poly &f, const Poly &g) {
    int f_l = f.size(), g_l = g.size();
    int lim = min(f_l, g_l);
    for (int i = 0; i < lim; i++)
        f[i] += g[i];
    return f;
}

Poly &operator-=(Poly &f, const Poly &g) {
    int f_l = f.size(), g_l = g.size();
    int lim = min(f_l, g_l);
    for (int i = 0; i < lim; i++)
        f[i] -= g[i];
    return f;
}

Poly operator+(const Poly &f, const Poly &g) {
    Poly ans(f);
    return ans += g;
}

Poly operator-(const Poly &f, const Poly &g) {
    Poly ans(f);
    return ans -= g;
}

#endif
