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
            return F.cut(p.first, p.second);
        };
        nr.exec = [&](pii p) {
            return G.cut(p.first, p.second);
        };
    }

    m32 next() {
        int len = now & -now;
        if (len < M) {
            u64 x = 0;
            for (int j = now & -M; j < now; ++j) {
                x += 1ull * G[j].v * F[now - j].v;
                if (j & 15)
                    x %= P;
            }
            G[now] += x % P;
        } else {
            int u = std::__lg(len / M) / std::__lg(B);
            int t = ++U[u] % (B - 1);
            len = (1 << (u * std::__lg(B))) * M;
            int l = now - len;
            vector<u64> ss(len * 2);
            for (int i = 0; i <= t; i++) {
                Poly &a = nr.get({len, l - i * len});
                Poly &b = nf.get({len * 2, len * i});
                a.ntt(len * 2), b.ntt(len * 2);
                for (int j = 0; j < len * 2; j++)
                    ss[j] += 1ull * a[j].v * b[j].v;
            }
            Poly s(len * 2);
            for (int i = 0; i < len * 2; i++)
                s[i] = ss[i] % P, ss[i] = 0;
            s.intt(len * 2);
            for (int i = len; i < std::min(len * 2, deg - l); i++)
                G[l + i] += s[i];
        }
        return G[now++];
    }
};

#endif