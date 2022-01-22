#ifndef ACM_NTT_INV_H
#define ACM_NTT_INV_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/cdq/0.hpp"

Poly Poly::inv() const {
    Poly G(deg());
    PolyCDQ X(*this, G);
    m32 iv = front().inv();
    G[0] = iv;
    for (int i = 1; i < deg(); i++)
        G[i] = -X.next() * iv;
    return G;
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
