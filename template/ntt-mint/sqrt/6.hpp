#ifndef ACM_NTT_SQRT_H
#define ACM_NTT_SQRT_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/inv/0.hpp"
#include "template/ntt-mint/mul/0.hpp"

Poly Poly::sqrt() const { //
    Poly x = {front().sqrt()};
    const int R = 16, iv2 = qpow(2);
    Poly T = Poly(*this).redeg(deg() * 2);
    x.push_back(at(1) * (x[0] * 2).inv());
    for (int t = 4; t < deg() * 2; t *= R) {
        int m = x.deg();
        vector<Poly> ng(R);
        ng[0] = Poly(x).ntt(m * 2);
        Poly h = x.inv();

        Poly cha_past = ng[0];
        mul(cha_past, cha_past, m * 2);
        for (int i = 0; i < m; i++)
            cha_past[i] = cha_past[i + m];

        h.ntt(2 * m);
        for (int k = 1; k < R; k++) {
            Poly cha(m * 2);
            for (int j = 1; j < k; j++)
                for (int i = 0; i < m * 2; i++)
                    cha[i] += ng[j][i] * ng[k - j][i];

            cha.intt(m * 2);
            for (int i = 0; i < m; i++)
                cha[i] += cha_past[i], cha_past[i] = cha[i + m];
            cha.fillZeroH(m * 2);
            for (int j = 0; j < m; j++)
                cha[j] = T[m * k + j] - cha[j];
            mul(cha, h, m * 2);
            cha.redeg(m);
            for (int i = 0; i < m; i++)
                cha[i] = cha[i] * iv2;

            x.resize((k + 1) * m);
            for (int i = 0; i < m; i++)
                x[m * k + i] = cha[i];
            if (x.deg() >= deg())
                break;

            ng[k] = cha;
            ng[k].ntt(m * 2);
            Poly tg = ng[k], g0 = ng[0];
            mul(tg, g0, m * 2);
            for (int i = 0; i < m; i++)
                cha_past[i] += tg[i + m] * 2;
        }
    }
    return x.cut(deg());
}

#endif
