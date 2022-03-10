#ifndef ACM_NTT_EXP_H
#define ACM_NTT_EXP_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/pre-inv/0.hpp"
#include "template/ntt-mint/cdq/0.hpp"

Poly Poly::exp() const {
    pre_inv(deg());
    Poly F = *this, G(deg());
    for (int i = 0; i < deg(); i++)
        F[i] *= i;
    PolyCDQ X(F, G);
    G[0] = 1;
    for (int i = 1; i < deg(); i++)
        G[i] = X.next() * Inv[i];
    return G;
}

#endif