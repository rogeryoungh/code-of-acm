#ifndef ACM_NTT_INV_H
#define ACM_NTT_INV_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/mul/0.hpp"

Poly &Poly::invD(Poly f2, Poly nx, int t) {
    mul(f2, nx, t).fillZeroL(t); // 6E
    mul(f2, nx, t); // 4E
    redeg(t);
    for (int i = t / 2; i < t; i++)
        (*this)[i] = -f2[i];
    return *this;
}

Poly Poly::inv() const { // 10E
    Poly x = {front().inv()};
    if (deg() == 1)
        return x;
    for (int t = 2; t < deg() * 2; t <<= 1)
        x.invD(cut(t), x.cut(t), t);
    return x.cut(deg());
}

Poly Poly::div(Poly f) const { // 12E
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
