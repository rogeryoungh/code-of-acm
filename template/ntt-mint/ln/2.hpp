#ifndef ACM_POLY_LN_H
#define ACM_POLY_LN_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/pre-inv/0.hpp"
#include "template/ntt-mint/inv/0.hpp"

Poly Poly::ln() const {
    Poly f = *this;
    pre_inv(deg());
    for (int i = 0; i < deg(); i++)
        f[i] *= i;
    f = f.div(*this);
    for (int i = 0; i < deg(); i++)
        f[i] *= Inv[i];
    return f;
}

#endif
