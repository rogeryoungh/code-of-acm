#ifndef ACM_NTT_SQRT_H
#define ACM_NTT_SQRT_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/pre-inv/0.hpp"
#include "template/ntt-mint/oc/0.hpp"

Poly Poly::sqrt() const {
    Poly G(deg());
    PolyOC X(G, G);
    G[0] = front().sqrt();
    m32 iv = (G[0] * 2).inv();
    for (int i = 1; i < deg(); i++) {
        G[i] = ((*this)[i] - X.next()) * iv;
    }
    return G;
}

#endif
