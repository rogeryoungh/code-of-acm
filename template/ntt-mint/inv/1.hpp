#ifndef ACM_NTT_INV_H
#define ACM_NTT_INV_H

#include "template/ntt-mint/poly/0.hpp"

Poly Poly::inv() const { // 12E
    Poly f = {front().inv()};
    for (int t = 2; t < deg() * 2; t <<= 1) {
        Poly u = cut(t);
        f.ntt(t * 2), u.ntt(t * 2); // 4E + 4E
        for (int i = 0; i < t * 2; i++)
            f[i] *= m32(2) - f[i] * u[i];
        f = f.intt(t * 2).fillZeroH(t * 2); // 4E
    }
    return f.cut(deg());
}

Poly Poly::div(Poly g) const { // 16E
    return (*this * g.redeg(deg()).inv()).cut(deg());
}

#endif
