#ifndef ACM_NTT_INV_H
#define ACM_NTT_INV_H


#include "template/ntt-mint/poly/0.hpp"

Poly Poly::inv() const { // 24E
    Poly f = {front().inv()};
    for (int t = 2; t < deg() * 2; t <<= 1) {
        f = f * (Poly{2} - (f * cut(t)).cut(t));
        f.redeg(t);
    }
    return f.cut(deg());
}

Poly Poly::div(Poly g) const { // 28E
    return (*this * g.redeg(deg()).inv()).cut(deg());
}

#endif
