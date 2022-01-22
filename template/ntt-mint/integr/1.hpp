#ifndef ACM_NTT_INTEGRATE_H
#define ACM_NTT_INTEGRATE_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/pre-inv/0.hpp"

Poly Poly::integr() const {
    Poly f(deg() + 1);
    pre_inv(deg() + 1);
    for (int i = deg(); i > 0; --i)
        f[i] = (*this)[i - 1] * Inv[i];
    return f;
}

#endif