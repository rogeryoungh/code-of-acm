#ifndef ACM_NTT_QUO_H
#define ACM_NTT_QUO_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/mul/0.hpp"
#include "template/ntt-mint/add/0.hpp"


Poly operator/(Poly f, Poly g) {
    int sz = f.deg() - g.deg() + 1;
    f = f.rev().cut(sz), g = g.rev();
    f = f * g.redeg(sz).inv();
    return f.cut(sz).rev();
}

pair<Poly, Poly> operator%(const Poly &F, const Poly &G) {
    auto Q = F / G;
    auto R = F - Q * G;
    R.redeg(G.deg() - 1);
    return {Q, R};
}

#endif
