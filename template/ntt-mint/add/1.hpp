#ifndef ACM_NTT_ADD_H
#define ACM_NTT_ADD_H

#include "template/ntt-mint/poly/0.hpp"

Poly operator+(const Poly &f, const Poly &g) {
    Poly ret = Poly(f).redeg(max(f.deg(), g.deg()));
    for (int i = 0; i < g.deg(); i++)
        f[i] += g[i];
    return f;
}

Poly operator-(const Poly &f, const Poly &g) {
    Poly ret = Poly(f).redeg(max(f.deg(), g.deg()));
    for (int i = 0; i < g.deg(); i++)
        f[i] -= g[i];
    return f;
}

m32 mulAt(const Poly &f, const Poly &g, int u) {
    int n = f.deg() - 1, m = g.deg() - 1;
    m32 ans = 0;
    for (int i = std::max(0, u - m); i <= std::min(u, n); i++)
        ans += f[i] * g[u - i];
    return ans;
}

#endif
