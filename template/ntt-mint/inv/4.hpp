#ifndef ACM_NTT_INV_H
#define ACM_NTT_INV_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/semi/0.hpp"

Poly Poly::inv() const {
    return PolySemi(*this).inv();
}

Poly Poly::div(Poly g) const {
    return PolySemi(g.redeg(deg())).quo(*this);
}

#endif
