#ifndef ACM_NTT_EXP_H
#define ACM_NTT_EXP_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/inv/2.hpp"
#include "template/ntt-mint/mul/0.hpp"
#include "template/ntt-mint/pre-inv/0.hpp"

Poly Poly::exp() const { // 20E
    if (deg() == 1)
        return {1};
    int lim = get_lim(deg());
    Poly f = {1, at(1)}, g = {1}, nf, ng = g;
    Poly dh = *this;
    for (int i = 0; i < dh.deg(); i++)
        dh[i] *= i;
    pre_inv(lim);
    for (int t = 4; t <= lim; t <<= 1) {
        nf = f.cut(t).ntt(t); // 2E
        ng = g.invD(nf, ng, t / 2); // 3E
        Poly nh = dh.cut(t);
        mul(nh, nf, t); // 4E
        for (int i = 0; i < t / 2; i++)
            nh[i] = nh[i + t / 2];
        nh.fillZeroH(t);
        mul(nh, ng, t); // 6E
        for (int i = t / 2; i < t; i++)
            nh[i] = nh[i - t / 2] * Inv[i];
        nh.fillZeroL(t);
        mul(nf, nh, t); // 4E
        f.resize(t);
        for (int i = t / 2; i < t; i++)
            f[i] = nf[i];
    }
    return f.cut(size());
}

#endif