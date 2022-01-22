#ifndef ACM_NTT_SQRT_H
#define ACM_NTT_SQRT_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/inv/0.hpp"
#include "template/ntt-mint/mul/0.hpp"

Poly Poly::sqrt() const {
    if (deg() == 1) {
        return {front().sqrt()};
    }
    const int R = 16, iv2 = qpow(2);
    int m = get_lim((deg() - 1) / R + 1);
    Poly x = cut(m).sqrt(), h = x.inv().ntt(m * 2);
    vector<Poly> ng(R);

    for (int k = 1; x.deg() < deg(); k++) {
        ng[k - 1] = x.cut(m, (k - 1) * m).ntt(m * 2);
        Poly psi(m * 2);
        for (int j = 0; j < k; j++) {
            if (j >= 1) {
                for (int i = 0; i < m; i++)
                    psi[i] -= ng[j][i] * (ng[k - j][i] + ng[k - 1 - j][i]);
                for (int i = m; i < m * 2; i++)
                    psi[i] -= ng[j][i] * (ng[k - j][i] - ng[k - 1 - j][i]);
            } else {
                for (int i = 0; i < m; i++)
                    psi[i] -= ng[j][i] * ng[k - 1 - j][i];
                for (int i = m; i < m * 2; i++)
                    psi[i] += ng[j][i] * ng[k - 1 - j][i];
            }
        }
        psi.intt(m * 2).fillZeroH(m * 2);
        for (int j = 0; j < min(m, deg() - m * k); j++)
            psi[j] += (*this)[m * k + j];
        mul(psi, h, m * 2);
        x.redeg((k + 1) * m);
        for (int i = 0; i < m; i++)
            x[m * k + i] = psi[i] * iv2;
    }
    return x.cut(deg());
}

#endif
