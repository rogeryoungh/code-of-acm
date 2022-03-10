#ifndef ACM_NTT_SQRT_H
#define ACM_NTT_SQRT_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/mul/0.hpp"
#include "template/ntt-mint/inv/2.hpp"

Poly Poly::sqrt() const { // 11E
    Poly x = {front().sqrt()}, g = x.inv(), ng = g;
    for (int t = 2; t < deg() * 2; t <<= 1) {
        const Poly &h = *this;
        Poly f = x;
        if (t >= 4) {
            g.invD(f.ntt(t / 2), ng, t / 2); // 3E
        }
        mul(f, f, t / 2); // 1E
        f.resize(t);
        for (int i = t / 2; i < std::min(h.deg(), t); i++)
            f[i] = h[i - t / 2] + h[i] - f[i - t / 2];
        ng = g;
        mul(f.fillZeroL(t), ng, t); // 6E
        x.resize(t);
        for (int i = t / 2; i < t; i++)
            x[i] = f[i] * ((P + 1) / 2);
    }
    return x.cut(size());
}

#endif
