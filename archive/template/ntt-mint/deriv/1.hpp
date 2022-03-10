#ifndef ACM_NTT_DERIVATIVE_H
#define ACM_NTT_DERIVATIVE_H

#include "template/ntt-mint/poly/0.hpp"

Poly Poly::deriv() const {
    Poly f(deg() - 1);
    for (int i = 1; i < deg(); i++)
        f[i - 1] = (*this)[i] * i;
    return f;
}

#endif
