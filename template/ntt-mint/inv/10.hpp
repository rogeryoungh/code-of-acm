#ifndef ACM_NTT_INV_H
#define ACM_NTT_INV_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/mul/0.hpp"

Poly Poly::inv() const { //
    if (deg() == 1) {
        return {front().inv()};
    }
    const int S = 1;
    int m = get_lim((deg() - 1) / (S * 3) + 1);
    Poly x = cut(m).inv(), h = Poly(x).ntt(m * 2);
    vector<Poly> nf(S * 3), ng(S * 3), nd(S * 2);

    for (int k = 0; k < 3 * S; k++)
        nf[k] = cut(m, k * m).ntt(m * 2);
    for (int k = 1; k < S; k++) {
        ng[k - 1] = x.cut(m, (k - 1) * m).ntt(m * 2);
        Poly psi(m * 2);
        for (int j = 0; j < k; j++) {
            for (int i = 0; i < m; i++)
                psi[i] -= ng[j][i] * (nf[k - j][i] + nf[k - 1 - j][i]);
            for (int i = m; i < m * 2; i++)
                psi[i] -= ng[j][i] * (nf[k - j][i] - nf[k - 1 - j][i]);
        }
        psi.intt(m * 2).fillZeroH(m * 2);
        mul(psi, h, m * 2);
        x.redeg((k + 1) * m);
        for (int i = 0; i < m; i++)
            x[m * k + i] = psi[i];
    }
    for (int k = 0; k < S; k++) {
        Poly dk(m * 2);
        for (int j = 0; j < k; j++) {
            for (int i = 0; i < m; i++)
                dk[i] += ng[j][i] * (nf[k + S - j][i] + nf[k + S - 1 - j][i]);
            for (int i = m; i < m * 2; i++)
                dk[i] += ng[j][i] * (nf[k + S - j][i] - nf[k + S - 1 - j][i]);
        }
        dk.intt(m * 2).fillZeroH(m * 2);
        nd[k] = dk.ntt(m * 2);
    }
    for (int k = S; k < S * 2; k++) {
        Poly dk(m * 2);
        for (int j = 0; j < k; j++) {
            if (j >= 1) {
                for (int i = 0; i < m; i++)
                    dk[i] += ng[j][i] * (ng[k - j][i] + ng[k - 1 - j][i]);
                for (int i = m; i < m * 2; i++)
                    dk[i] += ng[j][i] * (ng[k - j][i] - ng[k - 1 - j][i]);
            } else {
                for (int i = 0; i < m; i++)
                    dk[i] += ng[j][i] * ng[k - 1 - j][i];
                for (int i = m; i < m * 2; i++)
                    dk[i] -= ng[j][i] * ng[k - 1 - j][i];
            }
        }
        for (int j = 0; j < k; j++) {
            for (int i = 0; i < m; i++)
                dk[i] -= ng[j][i] * (nf[k + S - j][i] + nf[k + S - 1 - j][i]);
            for (int i = m; i < m * 2; i++)
                dk[i] -= ng[j][i] * (nf[k + S - j][i] - nf[k + S - 1 - j][i]);
        }
        dk.intt(m * 2).fillZeroH(m * 2);
        nd[k] = dk.ntt(m * 2);
    }
    for (int k = S; k < 3 * S; k++) {
        Poly gk(m * 2);
        for (int j = 0; j < k; j++) {
            for (int i = 0; i < m; i++)
                gk[i] -= ng[j][i] * (nf[k + S - j][i] + nf[k + S - 1 - j][i]);
            for (int i = m; i < m * 2; i++)
                gk[i] -= ng[j][i] * (nf[k + S - j][i] - nf[k + S - 1 - j][i]);
        }
    }
    return x.cut(deg());
}

Poly Poly::div(Poly f) const { //
    if (deg() == 1) {
        return {front() * f[0].inv()};
    }
    f.redeg(deg());
    const int R = 16;
    int m = get_lim((deg() - 1) / R + 1);
    Poly x = cut(m).div(f), h = f.cut(m).inv().ntt(m * 2);

    vector<Poly> nf(R), ng(R);

    nf[0] = f.cut(m).ntt(m * 2);
    for (int k = 1; x.deg() < deg(); k++) {
        nf[k] = f.cut(m, k * m).ntt(m * 2);
        ng[k - 1] = x.cut(m, (k - 1) * m).ntt(m * 2);
        Poly psi(m * 2);
        for (int j = 0; j < k; j++) {
            for (int i = 0; i < m; i++)
                psi[i] -= ng[j][i] * (nf[k - j][i] + nf[k - 1 - j][i]);
            for (int i = m; i < m * 2; i++)
                psi[i] -= ng[j][i] * (nf[k - j][i] - nf[k - 1 - j][i]);
        }
        psi.intt(m * 2).fillZeroH(m * 2);
        for (int j = 0; j < min(m, deg() - m * k); j++)
            psi[j] += (*this)[m * k + j];
        mul(psi, h, m * 2);
        x.redeg((k + 1) * m);
        for (int i = 0; i < m; i++)
            x[m * k + i] = psi[i];
    }
    return x.cut(deg());
}

#endif
