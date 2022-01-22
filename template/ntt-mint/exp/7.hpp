#ifndef ACM_NTT_EXP_H
#define ACM_NTT_EXP_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/inv/2.hpp"
#include "template/ntt-mint/mul/0.hpp"
#include "template/ntt-mint/pre-inv/0.hpp"

Poly Poly::exp() const { // 14E
    if (deg() == 1) {
        return {1};
    }
    const int S = 16;
    int m = get_lim((deg() - 1) / S + 1);
    Poly x = cut(m).exp(), u = x.inv();
    vector<Poly> nf(S), ng(S);

    Poly df = *this;
    for (int i = 0; i < df.deg(); i++)
        df[i] *= i;
    //dbg(df);
    u.ntt(m * 2);
    nf[0] = df.cut(m).ntt(m * 2);

    for (int k = 1; x.deg() < deg(); k++) {
        nf[k] = df.cut(m, k * m).ntt(m * 2);
        ng[k - 1] = x.cut(m, m * (k - 1)).ntt(m * 2);
        Poly psi(m * 2);
        for (int j = 0; j < k; j++) {
            for (int i = 0; i < m; i++)
                psi[i] += ng[j][i] * (nf[k - j][i] + nf[k - 1 - j][i]);
            for (int i = m; i < m * 2; i++)
                psi[i] += ng[j][i] * (nf[k - j][i] - nf[k - 1 - j][i]);
        }
        psi.intt(m * 2).fillZeroH(m * 2);

        mul(psi, u, m * 2).fillZeroH(m * 2);
        pre_inv(m * (k + 2));
        for (int i = 0; i < m * 2; i++)
            psi[i] *= Inv[m * k + i];
        mul(psi, ng[0], m * 2).fillZeroH(m * 2);
        x.redeg((k + 1) * m);
        for (int i = 0; i < m; i++)
            x[m * k + i] = psi[i];
    }
    return x.cut(deg());
}

#endif