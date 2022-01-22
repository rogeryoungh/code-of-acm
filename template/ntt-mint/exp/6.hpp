#ifndef ACM_NTT_EXP_H
#define ACM_NTT_EXP_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/pre-inv/0.hpp"
#include "template/ntt-mint/oc/0.hpp"

Poly Poly::exp() const {
    Poly f = *this, G(deg());
    pre_inv(deg());
    for (int i = 0; i < deg(); i++)
        f[i] *= i;
    PolyOC X(f, G);
    G[0] = 1;
    for (int i = 1; i < deg(); i++) {
        G[i] = (X.next() + f[i] * G[0]) * Inv[i];
    }
    return G;
}

#endif