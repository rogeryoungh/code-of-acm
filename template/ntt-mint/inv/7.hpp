#ifndef ACM_NTT_INV_H
#define ACM_NTT_INV_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/oc/0.hpp"

Poly Poly::inv() const {
    Poly G(deg());
    PolyOC X(*this, G);
    m32 iv = front().inv();
    G[0] = iv;
    for (int i = 1; i < deg(); i++) {
        G[i] = -(X.next() + X.F[i] * X.G[0]) * iv;
    }
    return G;
}

Poly Poly::div(Poly g) const {
    m32 iv = g[0].inv();
    Poly G(deg());
    PolyOC X(g.redeg(deg()), G);
    G[0] = front() * iv;
    for (int i = 1; i < deg(); i++) {
        G[i] = ((*this)[i] - X.next() - g[i] * G[0]) * iv;
    }
    return G;
}

#endif
