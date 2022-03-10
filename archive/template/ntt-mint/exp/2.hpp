#ifndef ACM_NTT_EXP_H
#define ACM_NTT_EXP_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/inv/2.hpp"
#include "template/ntt-mint/mul/0.hpp"
#include "template/ntt-mint/pre-inv/0.hpp"

Poly Poly::exp() const { // 17E
    if (size() == 1)
        return {1};
    int lim = get_lim(size());
    Poly f = {1, at(1)}, g = {1}, nf, ng = g;
    pre_inv(lim);
    for (int t = 4; t <= lim; t <<= 1) {
        nf = Poly(f).ntt(t); // 2E
        ng = g.invD(nf, ng, t / 2); // 3E

        Poly q = cut(t / 2);
        for (int i = 0; i < q.deg(); i++)
            q[i] *= i;
        mul(q, nf, t / 2); // 2E
        for (int i = 0; i < t / 2; i++)
            q[i] -= f[i] * i;
        mul(q, ng, t); // 6E
        for (int i = t / 2; i < t; i++)
            q[i] = q[i - t/ 2] * Inv[i];
        for (int i = t / 2; i < std::min(t, deg()); i++)
            q[i] += (*this)[i];
        mul(q.fillZeroL(t), nf, t); // 4E
        f.resize(t);
        for (int i = t / 2; i < t; i++)
            f[i] = q[i];
    }
    return f.cut(size());
}

#endif