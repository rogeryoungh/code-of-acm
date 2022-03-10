#ifndef ACM_NTT_DIV_H
#define ACM_NTT_DIV_H

#ifndef RYLOCAL
#include "__base.hpp"
#include "../basic/mint.hpp"
#include "../basic/qpow.hpp"
#include "../basic/inv.hpp"

#include "ntt.hpp"
#include "ntt_ln.hpp"
#include "ntt_exp.hpp"
#endif


// DIV 的结果和多项式的次数有关
Poly ntt_div(const Poly &F, int n, const Poly &G, int m) {
    int lim = get_lim(n, n);
    Poly FR(lim), GR(lim), gr_inv;

    copy_n(F.begin(), n, FR.rend() - n);
    int sz = min(m, n - m + 1);
    copy_n(G.begin() + m - sz, sz, GR.rend() - sz);

    gr_inv = ntt_inv(GR, lim / 2);
    gr_inv.resize(lim);

    FR *= gr_inv;

    FR.resize(n - m + 1);
    reverse(FR.begin(), FR.end());
    return FR;
}

pair<Poly, Poly> ntt_mod(const Poly &F, int n, const Poly &G, int m) {
    int lim = get_lim(n, n);
    Poly TG(G);
    Poly Q = ntt_div(F, n, G, m);

    Poly TQ(Q);
    TQ.resize(lim);

    TG *= TQ;
    Poly R(m - 1);
    for (int i = 0; i < m - 1; i++) {
        R[i] = F[i] - TG[i];
    }

    return {Q, R};
}

#endif
