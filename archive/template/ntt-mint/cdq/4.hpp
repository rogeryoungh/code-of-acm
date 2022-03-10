#ifndef ACM_NTT_CDQ_H
#define ACM_NTT_CDQ_H

#include "template/ntt-mint/poly/0.hpp"
#include "template/ntt-mint/cache/0.hpp"

struct PolyCDQ {
    int deg, now = 1;
    static const int M = 32, B = 16;
    const Poly &F;
    Poly &G;
    NttCache<pii> nr, nf;
    vector<int> U;

    PolyCDQ(const Poly &f, Poly &g) : F(f), G(g) {
        deg = F.size();
        U.resize(32, -1);
        nf.exec = [&](pii p) {
            return F.cut(p.first, p.second).ntt(p.first);
        };
        nr.exec = [&](pii p) {
            return G.cut(p.first, p.second).ntt(p.first * 2);
        };
    }

    m32 next() {
        int len = now & -now;
        if (len < M) {
            for (int j = now & -M; j < now; ++j)
                G[now] += G[j] * F[now - j];
        } else {
            int u = std::__lg(len / M) / std::__lg(B);
            int t = ++U[u] % (B - 1);
            len = (1 << (u * std::__lg(B))) * M;
            int l = now - len;
            Poly s(len * 2);
            for (int i = 0; i <= t; i++) {
                Poly &a = nr.get({len, l - i * len});
                Poly &b = nf.get({len * 2, len * i});
                for (int j = 0; j < len * 2; j++)
                    s[j] += a[j] * b[j];
            }
            s.intt(len * 2);
            for (int i = len; i < std::min(len * 2, deg - l); i++)
                G[l + i] += s[i];
        }
        return G[now++];
    }
};

#endif