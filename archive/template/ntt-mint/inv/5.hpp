#ifndef ACM_NTT_INV_H
#define ACM_NTT_INV_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/cdq/3.hpp"

Poly &Poly::invD(Poly f2, Poly nx, int t) {
    mul(f2, nx, t).fillZeroL(t); // 6E
    mul(f2, nx, t); // 4E
    resize(t);
    for (int i = t / 2; i < t; i++)
        (*this)[i] = -f2[i];
    return *this;
}

Poly Poly::inv() const { // 10E
    Poly x = {front().inv()};
    if (deg() == 1)
        return x;
    for (int t = 2; t < deg() * 2; t <<= 1)
        x.invD(cut(t), x.cut(t), t);
    return x.cut(deg());
}

Poly Poly::div(Poly g) const {
    Poly G(deg());
    PolyCDQ X(g.redeg(deg()), G);
    m32 iv = g[0].inv();
    G[0] = front() * iv;
    for (int i = 1; i < deg(); i++)
        G[i] = ((*this)[i] - X.next()) * iv;
    return G;
}

#endif
