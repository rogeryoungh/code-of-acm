#ifndef ACM_NTT_SQRT_H
#define ACM_NTT_SQRT_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/mul/0.hpp"
#include "template/ntt-mint/inv/2.hpp"

Poly Poly::sqrt() const { // 11E
    int lim = get_lim(deg()), iv2 = (P + 1) / 2;
    Poly x = {front().sqrt()};
    Poly g = x.inv(), ng = g;
    for (int t = 2; t <= lim; t <<= 1) {
        Poly f = x; // 2E
        if (t >= 4)
            ng = g.invD(f.ntt(t / 2), ng, t / 2); // 3E
        mul(f, f, t / 2).redeg(t);    // 1E
        for (int i = t / 2; i < min(t, deg()); i++)
            f[i] = (*this)[i - t / 2] + (*this)[i] - f[i - t / 2];
        mul(f.fillZeroL(t), ng, t); // 6E
        x.redeg(t);
        for (int i = t / 2; i < t; i++)
            x[i] = f[i] * iv2;
    }
    return x.cut(deg());
}

#endif
