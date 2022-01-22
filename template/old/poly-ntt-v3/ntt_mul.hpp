#ifndef ACM_POLY_MUL_H
#define ACM_POLY_MUL_H

#ifndef RYLOCAL
#include "__base.hpp"

#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#endif

auto operator+(Poly &f, int k) {
    return f.begin() + k;
}
auto operator+(const Poly &f, int k) {
    return f.begin() + k;
}

auto operator-(Poly &f, int k) {
    return f.end() - k;
}
auto operator-(const Poly &f, int k) {
    return f.end() - k;
}

Poly poly(Poly::iterator f, int k) {
    return Poly{f + 0, f + k};
}
Poly poly(const Poly &f, int k) {
    return Poly{f + 0, f + k};
}

using CALL = std::function<void(Mint&, Mint&)>;

CALL call_conv = [](Mint &fi, Mint &gi) {
    fi *= gi;
};

void online_conv(Poly &f, Poly &g, int n, const CALL& func = call_conv) {
    if (f.data() != g.data())
        g.resize(n), ntt(g);
    f.resize(n), ntt(f);
    for (int i = 0; i < n; i++)
        func(f[i], g[i]);
    intt(f);
}

Poly &operator*=(Poly &f, Poly &g) {
    const int n = f.size(), m = g.size(), lim = get_lim(n + m - 1);
    online_conv(f, g, lim);
    return f.resize(n + m - 1), f;
}

Poly &operator+=(Poly &f, const Poly &g) {
    const int n = f.size(), m = g.size(), lim = std::max(n, m);
    f.resize(lim);
    for (int i = 0; i < std::min(lim, m); i++)
        f[i] += g[i];
    return f;
}

Poly &operator-=(Poly &f, const Poly &g) {
    const int n = f.size(), m = g.size(), lim = std::max(n, m);
    f.resize(lim);
    for (int i = 0; i < std::min(lim, m); i++)
        f[i] -= g[i];
    return f;
}

Poly operator+(Poly f, const Poly g) {
    return f += g;
}
Poly operator-(Poly f, const Poly g) {
    return f -= g;
}
Poly operator*(Poly f, Poly g) {
    return f *= g, f;
}

#endif
