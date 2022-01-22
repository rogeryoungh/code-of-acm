#ifndef ACM_NTT_SQRT_H
#define ACM_NTT_SQRT_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/inv/0.hpp"
#include "template/ntt-mint/mul/0.hpp"

Poly Poly::sqrt() const { // 8E
    Poly x = {front().sqrt()};
    int R = 16, iv2 = qpow(2);
    Poly T = Poly(*this).redeg(deg() * 2);
    // 卡常，因为 1e5 ~ 2^17，把前面两块处理掉就快了
    x.push_back(at(1) * (x[0] * 2).inv());
    for (int t = 4; t < deg() * 2; t *= R) {
        int m = x.deg();
        vector<Poly> ng(R);
        Poly h = x.inv();

        h.ntt(2 * m);
        for (int k = 1; k < R; k++) {
            ng[k - 1] = x.cut(m, (k - 1) * m).ntt(m * 2);
            Poly psi(m * 2);
            for (int j = 0; j < k; j++) {
                if (j >= 1) {
                    for (int i = 0; i < m; i++)
                        psi[i] += ng[j][i] * (ng[k - j][i] + ng[k - 1 - j][i]);
                    for (int i = m; i < m * 2; i++)
                        psi[i] += ng[j][i] * (ng[k - j][i] - ng[k - 1 - j][i]);
                } else {
                    for (int i = 0; i < m; i++)
                        psi[i] += ng[j][i] * ng[k - 1 - j][i];
                    for (int i = m; i < m * 2; i++)
                        psi[i] -= ng[j][i] * ng[k - 1 - j][i];
                }
            }
            psi.intt(m * 2).fillZeroH(m * 2);
            for (int j = 0; j < m; j++)
                psi[j] = T[m * k + j] - psi[j];
            mul(psi, h, m * 2);
            x.redeg((k + 1) * m);
            dbg(x.deg());
            for (int i = 0; i < m; i++)
                x[m * k + i] = psi[i] * iv2;
            if (x.deg() >= deg())
                break;
        }
    }
    return x.cut(deg());
}

#endif
