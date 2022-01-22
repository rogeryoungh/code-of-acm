#ifndef ACM_NTT_MUL_H
#define ACM_NTT_MUL_H

#include "template/ntt-mint/poly/0.hpp"

Poly& mul(Poly &f, Poly &g, int t) {
    f.ntt(t), g.ntt(t);
    for (int i = 0; i < t; i++)
        f[i] *= g[i];
    return f.intt(t);
}

Poly operator*(Poly f, Poly g) {
    if (f.deg() < g.deg())
        swap(f, g);
    if (g.deg() == 1) {
        for (auto &fi : f)
            fi *= g[0];
        return f;
    }
    int t = f.deg() + g.deg() - 1;
    return mul(f, g, get_lim(t)).redeg(t);
}

#endif
